document.getElementById('input').addEventListener('keydown', function(e) {
  if (e.key === 'Tab') {
    e.preventDefault(); 
    var start = this.selectionStart;
    var end = this.selectionEnd;
    this.value = this.value.substring(0, start) + "\t" + this.value.substring(end);
    this.selectionStart = this.selectionEnd = start + 1;
  } else if (e.key === 'Enter') {
    e.preventDefault();
    var start = this.selectionStart;
    var end = this.selectionEnd;
    var lines = this.value.substring(0, start).split("\n");
    var currentLine = lines[lines.length - 1];
    var indentation = currentLine.match(/^\s*/)[0];
    this.value = this.value.substring(0, start) + "\n" + indentation + this.value.substring(end);
    var newPos = start + indentation.length + 1;
    this.selectionStart = this.selectionEnd = newPos;
  }
});


const updateOutputScroll = () => {
  var div = document.getElementById("output");
  div.scrollTop = div.scrollHeight;
};

const transpile = (input) => {
  if (input == "") return ""
  const func = Module.cwrap("transpile", "string", ["string"])
  try {
    const result = func(input)
    return result
  } catch(error) {
    return ""
  }
}

const getRunLink = () => {
  const baseString = "https://cpp.sh/?source="
  const source = document.getElementById("output").textContent
  const encodedSource = encodeURIComponent(source);
  return baseString + encodedSource
}

const onInputChange = () => {
  const input = document.getElementById("input").value
  const output = transpile(input)
  document.getElementById("output").textContent = output
  updateOutputScroll()
  var element = document.getElementById("output");
  if (element.dataset.highlighted) {
      element.dataset.highlighted = "";
  }
  hljs.highlightAll()

  var compiler = document.getElementById('compiler');
  compiler.src = createCompilerExplorerUrl(output)
}

export function risonify(obj) {
  return rison.quote(rison.encode_object(obj));
}

export function unrisonify(text) {
  return rison.decode_object(decodeURIComponent(text.replace(/\+/g, '%20')));
}

const createCompilerExplorerUrl = (source) => {
  const encoded = risonify({source})
  const before = "g:!((g:!((h:codeEditor,i:(filename:'1',fontScale:14,fontUsePx:'0',j:1,lang:c%2B%2B,selection:(endColumn:1,endLineNumber:1,positionColumn:1,positionLineNumber:1,selectionStartColumn:1,selectionStartLineNumber:1,startColumn:1,startLineNumber:1),"
  const after = "),l:'5',n:'0',o:'C%2B%2B+source+%231',t:'0'),(h:executor,i:(argsPanelShown:'1',compilationPanelShown:'0',compiler:g132,compilerName:'',compilerOutShown:'0',execArgs:'',execStdin:'',fontScale:14,fontUsePx:'0',j:1,lang:c%2B%2B,libs:!(),options:'',source:1,stdinPanelShown:'1',wrap:'1'),l:'5',n:'0',o:'Executor+x86-64+gcc+13.2+(C%2B%2B,+Editor+%231)',t:'0')),k:100,l:'4',n:'0',o:'',s:1,t:'0')),version:4"
  const totalString = before + encoded + after
  const compressed = LZString.compressToBase64(totalString);
  const compressedUriEncoded = encodeURIComponent(compressed)
  const fullLink = "https://godbolt.org/e?hideEditorToolbars=true#z:" + compressedUriEncoded
  return fullLink
}

const onWindowLoad = () => {
  window.onload = hljs.highlightAll()
  var string = "This is my compression test.";
  var compressed = LZString.compressToBase64(string);
  console.log({compressed})
}

window.onload = onWindowLoad
document.getElementById('input').addEventListener('input', onInputChange);