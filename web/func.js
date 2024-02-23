document.getElementById("runButton").addEventListener("click", () => {
    const func = Module.cwrap("transpile", "string", ["string"])
    console.log(func("x = 77"))
    // const result = Module.ccall(
    //   "transpile", // name of C function
    //   [Number], // return type
    //   [Number], // argument types
    //   [2], // arguments
    // );
    // console.log(result)
  });