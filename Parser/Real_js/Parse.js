/*
@ Description: 
The final code like the below:
    var ast = parse(TokenStream(InputStream(code)));

The maybe_* functions

These functions check what follows after 
an expression in order to decide whether
 to wrap that expression in another node, 
 or just return it as is.

{
  type: "prog",
  prog: [
    // first line:
    {
      type: "assign",
      operator: "=",
      left: { type: "var", value: "sum" },
      right: {
        type: "lambda",
        vars: [ "a", "b" ],
        body: {
          // the body should be a "prog", but because
          // it contains a single expression, our parser
          // reduces it to the expression itself.
          type: "binary",
          operator: "+",
          left: { type: "var", value: "a" },
          right: { type: "var", value: "b" }
        }
      }
    },
    // second line:
    {
      type: "call",
      func: { type: "var", value: "print" },
      args: [{
        type: "call",
        func: { type: "var", value: "sum" },
        args: [ { type: "num", value: 1 },
                { type: "num", value: 2 } ]
      }]
    }
  ]
}
*/


var FALSE = { type: "bool", value: false };

function parse(token) {
    //operator precedence
    // precedence up with number
    // like * 20 + 10
    var PRECEDENCE = {
        "=": 1,
        "||": 2,
        "&&": 3,
        "<": 7,
        ">": 7,
        "<=": 7,
        ">=": 7,
        "==": 7,
        "!=": 7,
        "+": 10,
        "-": 10,
        "*": 20,
        "/": 20,
        "%": 20,
    };
    return parse_toplevel();

    function is_punc(ch) {
        var tok = token.peek();
        return tok && tok.type == "punc" && (!ch || tok.value == ch) && tok;
    }

    function is_kw(kw) {
        var tok = token.peek();
        return tok && tok.type == "kw" && (!kw || tok.value == kw) && tok;
    }

    function is_op(op) {
        var tok = token.peek();
        return tok && tok.type == "op" && (!op || tok.value == op) && tok;
    }

    function skip_punc(ch) {
        if (is_punc(ch)) token.next();
        else token.croak("Expecting punctuation: \"" + ch + "\"");
    }

    function skip_kw(kw) {
        if (is_kw(kw)) token.next();
        else token.croak("Expecting keyword: \"" + kw + "\"");
    }

    function skip_op(op) {
        if (is_op(op)) token.next();
        else token.croak("Expecting operator: \"" + op + "\"");
    }

    function unexpected() {
        token.croak("Unexpected token: " + JSON.stringify(token.peek()));
    }

    // compose binary expressions like 1 + 2 * 3
    function maybe_binary(left, my_prec) {
        var tok = is_op();
        if (tok) {
            var his_prec = PRECEDENCE[tok.value];
            if (his_prec > my_prec) {
                token.next();
                return maybe_binary({
                    type: tok.value == "=" ? "assign" : "binary",
                    operator: tok.value,
                    left: left,
                    right: maybe_binary(parse_atom(), his_prec)
                }, my_prec);
            }
        }
        return left;
    }

    // delimited("(", ")", ",", parse_varname)
    // a vector has all the items
    function delimited(start, stop, separator, parser) {
        var a = [],
            first = true;
        skip_punc(start);
        while (!token.eof()) {
            if (is_punc(stop)) break;
            if (first) first = false;
            else skip_punc(separator);
            if (is_punc(stop)) break;
            a.push(parser());
        }
        skip_punc(stop);
        return a;
    }

    function parse_call(func) {
        return {
            type: "call",
            func: func,
            args: delimited("(", ")", ",", parse_expression),
        };
    }

    function parse_varname() {
        var name = token.next();
        if (name.type != "var") token.croak("Expecting variable name");
        return name.value;
    }

    function parse_if() {
        skip_kw("if");
        var cond = parse_expression();
        if (!is_punc("{")) skip_kw("then");
        var then = parse_expression();
        var ret = {
            type: "if",
            cond: cond,
            then: then,
        };
        if (is_kw("else")) {
            token.next();
            ret.else = parse_expression();
        }
        return ret;
    }

    // the lambda has been eaten
    // just care the arguments
    // but they are in parentheses and delimited by commas
    function parse_lambda() {
        return {
            type: "lambda",
            vars: delimited("(", ")", ",", parse_varname),
            body: parse_expression()
        };
    }

    function parse_bool() {
        return {
            type: "bool",
            value: token.next().value == "true"
        };
    }

    function maybe_call(expr) {
        expr = expr();
        return is_punc("(") ? parse_call(expr) : expr;
    }

    // main dispatching job, depending on the current token
    function parse_atom() {
        return maybe_call(function() {
            if (is_punc("(")) {
                token.next();
                var exp = parse_expression();
                skip_punc(")");
                return exp;
            }
            if (is_punc("{")) return parse_prog();
            if (is_kw("if")) return parse_if();
            if (is_kw("true") || is_kw("false")) return parse_bool();
            if (is_kw("lambda") || is_kw("λ")) {
                token.next();
                return parse_lambda();
            }
            var tok = token.next();
            if (tok.type == "var" || tok.type == "num" || tok.type == "str")
                return tok;
            unexpected();
        });
    }

    //every line(;) 
    //return the whole program
    function parse_toplevel() {
        var prog = [];
        while (!token.eof()) {
            prog.push(parse_expression());
            if (!token.eof()) skip_punc(";");
        }
        return { type: "prog", prog: prog };
    }

    function parse_prog() {
        var prog = delimited("{", "}", ";", parse_expression);
        if (prog.length == 0) return FALSE;
        if (prog.length == 1) return prog[0];
        return { type: "prog", prog: prog };
    }

    function parse_expression() {
        return maybe_call(function() {
            return maybe_binary(parse_atom(), 0);
        });
    }
}

// a = {
//     fib(10);  # has no side-effects, but it's computed anyway
//     fib(15)   # the last semicolon can be missing
//   };
//   print(a); # prints 610