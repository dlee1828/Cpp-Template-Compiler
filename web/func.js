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
    return "syntax error"
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
  var iFrame = document.getElementById('oc-editor');
  iFrame.contentWindow.postMessage({
      eventType: 'populateCode',
      language: 'python',
      files: [
      {
        "name": "HelloWorld.py",
        "content": output
      }
  ]
  }, "*");
}

const onRunClicked = () => {
  window.open(getRunLink(), "_blank")
}


window.onload = hljs.highlightAll()
document.getElementById('input').addEventListener('input', onInputChange);
document.getElementById('run-button').addEventListener('click', onRunClicked);