const readline = require('node:readline/promises');
const { stdin: input, stdout: output } = require('node:process');

function indent(s, indentSize) {

    var capture = RegExp(/(.*LAYOUT_split_3x5_2\()(.*)(\).*)/).exec(s)
    var prelude = capture[1];
    var middle = capture[2];
    var ending = capture[3];

    const tokens = splitIntoTokens(middle)

    const NUM_COLS = 10;
    const NUM_ROWS = 3;
    const INNER_COLS = [3,4,5,6]
    
    const cols = organizeIntoColumns(tokens, NUM_COLS, NUM_ROWS, INNER_COLS)
    
    const prettyMiddle = printColumns(cols, NUM_COLS, NUM_ROWS, indentSize * 2);
    
    const output =`${spaces(indentSize)}${prelude}\n${prettyMiddle}\n${spaces(indentSize)}${ending}`

    console.log(output)
}

function printColumns(cols, numCols, numRows, indentSize) {
    const colWidths = cols.map(c => maxWidth(c, 0))
    let output = spaces(indentSize);
    numRows += 1

    for(let i = 0; i < numRows; i++) {
        for(let j = 0; j < numCols; j++) {
            let value = '';
            if(i >= cols[j].length) {
               value = ''
            } else {
                value = cols[j][i];
            }

            let padded = pad(value, colWidths[j])
            
            output += padded + spaces(3)
            if(j == (numCols / 2) - 1) {
                output += '\t\t'
            }
        }
        if(i !== numRows - 1) {
            output += '\n' + spaces(indentSize)
        }
    }
    return output
}


function splitIntoTokens(body) {
    let modifier_depth = 0;
    let buf = '';
    let tokens = [];
    for (let c of body) {
        if(c == '(') {
            modifier_depth++;
        }
        if (c == ')') {
            modifier_depth--;
        }
        if (modifier_depth == 0 && c == ',') {
            tokens.push(buf.trim())
            buf = '';
            continue
        }
        buf += c;
    }
    tokens.push(buf.trim())
    return tokens;
}

function organizeIntoColumns(tokens, numCols, numRows, innerCols) {
    let cols = [];
    for(let i = 0; i < numCols; i ++) {
        cols.push([])
    }

    for(let i = 0; i < tokens.length; i ++) {
        let colIdx = 0;
        if(i < numRows*numCols) {
            colIdx = i % numCols
        } else {
            // use a different placement method for the 4 keys at the bottom of the
            // keyboard
            let innerColIdx = i % (numRows*numCols);
            colIdx = innerCols[innerColIdx];
        }

        let token = tokens[i];
        if(i != tokens.length - 1) {
            token += ','
        }

        cols[colIdx].push(token)
    }
    return cols
}


function pad(value, width) {
    let toPad = width - value.length;
    if (toPad <= 0) {
        return value;
    }

    return value + spaces(toPad)
}

function spaces(n) {
    let out = '';
    for(let i = 0; i < n; i++) {
        out += ' '
    }
    return out;
}

function maxWidth(col, padding) {
    let width = 0;
    for(let item of col) {
        let _w = item.length + padding
        if (_w > width) {
            width = _w
        }
    }
    return width;
}

async function main() {
    const rl = readline.createInterface({ input, output });
    for(;;) {
        const input = await rl.question('Paste layer to be formatted\n\n')
        console.log('\n\n')
        indent(input, 4)
    }
}

main()



