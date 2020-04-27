extern crate rand;


use rand::Rng;
use clap::{Arg, App};
use std::thread;
use std::sync::mpsc;    
use std::sync::mpsc::Receiver;


/**
Un viejo banquero retirado se mudó a vivir al campo lejos de toda la tecnología.
Para vivir, invierte la plata que hizo durante sus años de trabajo mediante
los amigos que tiene en diversos fondos de inversión.
Al inicio de cada semana les envía por correo el dinero para invertir a sus amigos;
luego espera hasta el final de la semana a que le envíen a su buzón el resultado de esas inversiones.
Modelar la situación planteada en Rust, considerando que:

        ◦ A todos los amigos les envía el mismo monto
        ◦ Que el dinero resultante lo vuelve a invertir la próxima semana
        ◦ Que las inversiones pueden dar una ganancia entre -50% y 50% de lo invertido.
*/

#[derive(Default)]
pub struct Arguments {
    initial_amount: f64,
    friends: i64,
}

impl Arguments {
    pub fn new(initial_amount: f64, friends: i64) -> Self {
        Arguments {
            initial_amount,
            friends,
        }
    }
    // Immutable access.

}

fn parse_args() -> Arguments {
    let matches = App::new("Banquero")
        .version("1.0.0")
        .author("Jazmin Ferreiro  <jazminsofiaf@gmail.com>")
        .arg(Arg::with_name("amount")
            .short("-a")
            .long("-a")
            .takes_value(true)
            .required(true)
            .default_value("0.0")
            .help(" Initial amount of many to invest  "))
        .arg(Arg::with_name("friends")
            .short("-f")
            .long("-f")
            .takes_value(true)
            .required(true)
            .default_value("0.0")
            .help("How many friends the banker has"))
        .get_matches();

    let numeric_amount:f64 = matches.value_of("amount").unwrap_or_default().parse::<f64>().unwrap_or_else(|_| {
        println!("Error in argument, expected numeric initial amount");
        return 0.0;
    });

    let friends :i64= matches.value_of("friends").unwrap_or_default().parse::<i64>().unwrap_or_else(|_| {
        println!("Error in argument, expected number of friends");
        return 0;
    });
    return Arguments::new(numeric_amount, friends);
}


struct Friend {
    thread: Option<thread::JoinHandle<()>>,
    result: Receiver<f64>,
}

impl Friend {
    fn invest(amount: f64) -> Friend {
        let (money_sender , money_receiver) = mpsc::channel::<f64>();
        let thread = thread::spawn(move || {
            if amount <= 0.0{
                money_sender.send( 0.0).unwrap();
            }
            let mut rng = rand::thread_rng();
            let result = amount + rng.gen_range(-0.5 * amount, 0.5 * amount);
            println!("Friend: I will return you  {:.3} dollars ",result);
            money_sender.send(result).unwrap();
        });
        Friend {
            thread: Some(thread),
            result: money_receiver,
        }
    }
    fn wait_investment_result(&mut self)-> f64{
        match self.thread.take() {
            Some(th)=> {
                th.join().expect("Error joining the thread");
                return self.result.recv().expect("Error receiving money");
            },
            _ => 0.0
        }
    }
}


fn round(num : f64)-> f64{
    return (num * 100.0).round() / 100.0;
}

fn main() {
    let args = parse_args();

    println!("Hi! I'm the banker, the savings of all my life are {} dollars", args.initial_amount);
    println!("I have {} friends who will help me to invest", args.friends);
    let mut amount = args.initial_amount;
    while round(amount) > 0.0 && args.friends > 0 {


        let mut friends_investments = Vec::new();

        for _ in  0..args.friends {
            let initial_amount = round(amount/args.friends  as f64);
            println!("Banker: sending  {:.3} dollars to my friend",initial_amount );
            let friend = Friend::invest(initial_amount);
            friends_investments.push(friend);

        }

        //espero a que todos terminene
       let  sum = friends_investments.into_iter().map(|mut friend| friend.wait_investment_result()).sum::<f64>();

        println!("Banker: the result of the investment was {:.3} dollars", sum);
        amount = sum;
    }


}
