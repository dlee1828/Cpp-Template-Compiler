const transpile = (input) => {
  const func = Module.cwrap("transpile", "string", ["string"])
  try {
    const result = func(input)
    return result
  } catch(error) {
    return "syntax error"
  }
}

const handleButtonClicked = () => {
  const input = document.getElementById("input").value
  const output = transpile(input)
  console.log({output})
  document.getElementById("output").innerText = output
}

document.getElementById("runButton").addEventListener("click", handleButtonClicked)