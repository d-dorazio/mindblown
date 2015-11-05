use ast::Token;
use ast::Token::*;

#[derive(Debug, PartialEq, Eq)]
pub enum ParserErr {
    BracketsMismatch
}

pub fn parse(s: &str) -> Result<Vec<Token>, ParserErr> {
    let mut loops: Vec<Vec<Token>> = vec![vec![]];

    for tok in s.chars() {
        let idx = loops.len() - 1;

        match tok {
            '+' => loops.get_mut(idx).unwrap().push(Plus),
            '-' => loops.get_mut(idx).unwrap().push(Minus),
            '>' => loops.get_mut(idx).unwrap().push(ShiftR),
            '<' => loops.get_mut(idx).unwrap().push(ShiftL),
            '.' => loops.get_mut(idx).unwrap().push(Out),
            ',' => loops.get_mut(idx).unwrap().push(In),
            '[' => loops.push(vec![]),
            ']' => {
                if loops.len() > 1 {
                    let l = loops.pop().unwrap();
                    loops.get_mut(idx - 1).unwrap().push(Loop(l));
                }
                else {
                    return Err(ParserErr::BracketsMismatch);
                }
            },
            _ => {
                // ignore every other character
            }
        }
    }

    if loops.len() != 1 {
        return Err(ParserErr::BracketsMismatch);
    }

    Ok(loops.pop().unwrap())
}

#[cfg(test)]
mod tests {
    use super::parse;

    use ast::Token;
    use ast::Token::*;

    fn check_ok(s: &str, t: Vec<Token>) {
        assert_eq!(parse(s).ok().unwrap(), t);
    }

    #[test]
    fn parse_test_ok() {
        check_ok("+", vec![Plus]);
        check_ok("-", vec![Minus]);
        check_ok(">", vec![ShiftR]);
        check_ok("<", vec![ShiftL]);
        check_ok(".", vec![Out]);
        check_ok(",", vec![In]);
        check_ok("+-><.,", vec![Plus, Minus, ShiftR, ShiftL, Out, In]);

        check_ok("[]", vec![Loop(vec![])]);
        check_ok("[+-]", vec![Loop(vec![Plus, Minus])]);

        check_ok("[[,.][]]", vec![Loop(vec![Loop(vec![In, Out]), Loop(vec![])])]);
    }

    #[test]
    #[should_panic]
    fn parse_test_panic() {
        check_ok("[", vec![]);
    }

    #[test]
    #[should_panic]
    fn parse_test_panic2() {
        check_ok("]", vec![]);
    }

    #[test]
    #[should_panic]
    fn parse_test_panic3() {
        check_ok("[[]", vec![]);
    }

    #[test]
    #[should_panic]
    fn parse_test_panic4() {
        check_ok("[]]", vec![]);
    }
}