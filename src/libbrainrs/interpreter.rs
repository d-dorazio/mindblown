use std::io;
use std::io::Write;
use std::num::Wrapping;

use ast::Token;
use ast::Token::*;

#[derive(Debug, PartialEq, Eq)]
pub struct State {
    lcells: Vec<Wrapping<u8>>,
    cur: Wrapping<u8>,
    rcells: Vec<Wrapping<u8>>
}

impl State {
    pub fn new() -> State {
        State {
            lcells: vec![],
            cur: Wrapping(0),
            rcells: vec![]
        }
    }

    pub fn plus(&mut self) {
        self.cur = self.cur + Wrapping(1);
    }
    
    pub fn minus(&mut self) {
        self.cur = self.cur - Wrapping(1);
    }
    
    pub fn shiftl(&mut self) {
        self.rcells.push(self.cur);
        self.cur = if self.lcells.len() > 0 {
            self.lcells.pop().unwrap()
        }
        else {
            Wrapping(0)
        }
    }

    pub fn shiftr(&mut self) {
        self.lcells.push(self.cur);
        self.cur = if self.rcells.len() > 0 {
            self.rcells.pop().unwrap()
        }
        else {
            Wrapping(0)
        }
    }

    pub fn inp(&mut self) {
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        
        while input.len() == 0 {
            io::stdin().read_line(&mut input).unwrap();
        }
        self.cur = Wrapping(input.as_bytes()[0]);
    }

    pub fn out(&self) {
        let Wrapping(c) = self.cur; 
        print!("{}", c as char);
        let _ = io::stdout().flush();
    }
}

pub fn interpret(ts: &Vec<Token>, st: &mut State) {
    for t in ts.iter() {
        match t {
            &Plus => st.plus(),  
            &Minus => st.minus(),
            &ShiftR => st.shiftr(),
            &ShiftL => st.shiftl(),
            &In => st.inp(),
            &Out => st.out(),
            &Loop(ref inner) => {
                while st.cur != Wrapping(0) {
                    interpret(&inner, st);
                }
            }
        };
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    use std::num::Wrapping;

    #[test]
    fn state_test() {
        let mut state = State::new();

        state.plus();
        assert_eq!(state, State {
            cur: Wrapping(1),
            lcells: vec![],
            rcells: vec![]
        });

        state.shiftr();
        assert_eq!(state, State {
            cur: Wrapping(0),
            lcells: vec![Wrapping(1)],
            rcells: vec![]
        });

        state.shiftl();
        assert_eq!(state, State {
            cur: Wrapping(1),
            lcells: vec![],
            rcells: vec![Wrapping(0)]
        });

        state.minus();
        assert_eq!(state, State {
            cur: Wrapping(0),
            lcells: vec![],
            rcells: vec![Wrapping(0)]
        });

    }
}