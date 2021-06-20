function InputStream(code) {
    var pos = 0, //position
        line = 1, //the row
        col = 0; //the column
    return {
        next: next,
        peek: peek,
        eof: eof,
        croak: croak,
    };

    function next() {
        var ch = code.charAt(pos++);
        if (ch == "\n") line++, col = 0;
        else col++;
        return ch;
    }

    function peek() {
        return code.charAt(pos);
    }

    function eof() {
        return peek() == "";
    }

    function croak(msg) {
        throw new Error(msg + " (" + line + ":" + col + ")");
    }
}

function TokenStream(input) {
    var current = null;
    var keywords = " if then else lambda λ true false ";
    return {
        next: next,
        peek: peek,
        eof: eof,
        croak: input.croak
    };

    // all arg as ch will test char type(string size:1) and return
    // a boolean value to tell the result.
    function is_keyword(word) {
        return keywords.indexOf(" " + word + " ") >= 0;
    }

    function is_digit(ch) { // /i means ignore case
        return /[0-9]/i.test(ch);
    }

    function is_id_start(ch) {
        return /[a-zλ_]/i.test(ch);
    }

    function is_id(ch) {
        return is_id_start(ch) || "?!-<>=0123456789".indexOf(ch) >= 0;
    }
    // operator
    function is_op_char(ch) {
        return "+-*/%=&|<>!".indexOf(ch) >= 0;
    }
    // punctuation 
    function is_punc(ch) {
        return ",;(){}[]".indexOf(ch) >= 0;
    }

    function is_whitespace(ch) {
        return " \t\n".indexOf(ch) >= 0;
    }

    function read_while(predicate) {
        var str = "";
        // !eof & predicate true will get the str
        // overall, it return word, not char.
        while (!input.eof() && predicate(input.peek()))
            str += input.next();
        return str;
    }

    // all read_* will return the token as AST node
    function read_number() {
        var has_dot = false;
        var number = read_while(function(ch) {
            if (ch == ".") {
                // tow dot not means num
                if (has_dot) return false;
                // note got a dot for floating num
                has_dot = true;
                return true;
            }
            return is_digit(ch);
        });
        return { type: "num", value: parseFloat(number) };
    }

    // judge whether is identifier
    function read_ident() {
        var id = read_while(is_id);
        return {
            type: is_keyword(id) ? "kw" : "var",
            value: id
        };
    }

    // pending
    function read_escaped(end) {
        var escaped = false,
            str = "";
        input.next(); // the first start(" ) ignore
        // use if else to replace continue style
        while (!input.eof()) {
            var ch = input.next();
            if (escaped) {
                str += ch;
                escaped = false;
            } else if (ch == "\\") {
                escaped = true;
            } else if (ch == end) {
                break;
            } else {
                str += ch;
            }
        }
        return str;
    }

    function read_string() {
        return { type: "str", value: read_escaped('"') };
    }

    function skip_comment() {
        read_while(function(ch) { return ch != "\n" });
        input.next();
    }

    function read_next() {
        read_while(is_whitespace); // input will arrived at first char(/S)
        if (input.eof()) return null;
        var ch = input.peek(); // not eaten
        if (ch == "#") {
            skip_comment(); // not interpreter comment. skip it
            return read_next();
        }
        if (ch == '"') return read_string();
        if (is_digit(ch)) return read_number();
        if (is_id_start(ch)) return read_ident();
        if (is_punc(ch)) return {
            type: "punc",
            value: input.next()
        };
        if (is_op_char(ch)) return {
            type: "op",
            value: read_while(is_op_char)
        };
        input.croak("Can't handle character: " + ch);
    }

    function peek() {
        return current || (current = read_next());
    }

    function next() {
        var tok = current;
        current = null;
        return tok || read_next();
    }

    function eof() {
        return peek() == null;
    }
}

// code = "if else \"hello world\" quote;";

// token = TokenStream(InputStream(code));

// console.log(token);
// console.log(token.next());
// console.log(token.next());
// console.log(token.peek());
// console.log(token.next());
// console.log(token.next());
// console.log(token.next());
// console.log(token.next());

// { next: [Function: next],
//     peek: [Function: peek],
//     eof: [Function: eof],
//     croak: [Function: croak] }
//   { type: 'kw', value: 'if' }
//   { type: 'kw', value: 'else' }
//   { type: 'str', value: 'hello world' }
//   { type: 'str', value: 'hello world' }
//   { type: 'var', value: 'quote' }
//   { type: 'punc', value: ';' }
//   null