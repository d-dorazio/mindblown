#[derive(Debug, PartialEq, Eq)]
pub enum Token {
    Plus,
    Minus,
    ShiftR,
    ShiftL,
    In,
    Out,
    Loop(Vec<Token>)
}

impl ToString for Token {
    fn to_string(&self) -> String {
        match self {
            &Token::Plus => "+".to_string(),
            &Token::Minus => "-".to_string(),
            &Token::ShiftR => ">".to_string(),
            &Token::ShiftL => "<".to_string(),
            &Token::In => ",".to_string(),
            &Token::Out => ".".to_string(),
            &Token::Loop(ref inner) => {
                format!("[{}]", inner.iter().map(|x| x.to_string()).collect::<String>())
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::Token;
    use super::Token::*;

    fn check(t: Token, s: &str) {
        assert_eq!(t.to_string(), s);
    }

    #[test]
    fn to_string_test() {
        check(Plus, "+");
        check(Minus, "-");
        check(ShiftR, ">");
        check(ShiftL, "<");
        check(In, ",");
        check(Out, ".");
        check(Loop(vec![]), "[]");
        check(Loop(vec![Plus, Minus]), "[+-]");
        check(Loop(vec![Loop(vec![In, Out]), Loop(vec![])]), "[[,.][]]");
    }
}