/*
@ Description: 
The final code like the below:
    var ast = parse(TokenStream(InputStream(code)));

    
@ Args: The code is a string value.
@ Return: It will return an object include 4 value
1. the next char
2. the pos char
3. whether eof
4. throw an error

@ Running: Every time running the object function will update the old stream object.
You can see the test example.

@ Note: Closure: U can just take the outer function as an object.
and the inner function is public member, the inner varible is private member.
*/

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


// Test:

// code = 'select id from student;';
// input = InputStream(code);
// console.log(input);
// console.log(input.next());
// console.log(input.next());
// console.log(input.peek());
// console.log(input.next());
// input.eof();

// Object { next: next(), peek: peek(), eof: eof(), croak: croak() } 

// s
// e
// l
// l