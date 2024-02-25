import os
import subprocess

test_code_path = "testing/tests"
test_expected_path = "testing/expected-output"
test_file_names = [
    "binary.txt",
    "fibonacci.txt",
    "gcd.txt",
    "n-choose-k.txt",
    "primes.txt",
    "pythagorean-triples.txt",
    "rounding.txt",
]

main_cpp_file = "src/main.cpp"


def set_running_tests_flag(value: bool):
    with open(main_cpp_file) as file:
        lines = file.readlines()
        for i, line in enumerate(lines):
            if "#define RUNNING_TESTS" in line.strip():
                lines[i] = f"#define RUNNING_TESTS {'true' if value else 'false'}\n"
    with open(main_cpp_file, "w") as file:
        file.writelines(lines)


def make_transpiled_cpp_file(test_file_name: str):
    test_file_path = f"{test_code_path}/{test_file_name}"
    os.system(f"./src/main {test_file_path} testing/transpiled.cpp")


def get_stdout_of_transpiled_cpp() -> str:
    os.system("clang++ -std=c++20 -o testing/transpiled testing/transpiled.cpp")
    result = subprocess.run(
        "./testing/transpiled",
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
    )
    return result.stdout


def compare_stdout_to_expected(test_file_name: str, stdout: str) -> bool:
    with open(f"{test_expected_path}/{test_file_name}") as file:
        expected = file.read()
        return stdout == expected


def run_test(test_file_name: str) -> bool:
    make_transpiled_cpp_file(test_file_name)
    stdout = get_stdout_of_transpiled_cpp()
    result = compare_stdout_to_expected(test_file_name, stdout)
    return result


def run_all_tests():
    set_running_tests_flag(True)
    os.system("cd src && make")
    passed_count = 0
    for test_file_name in test_file_names:
        result = run_test(test_file_name)
        print(f"Test for {test_file_name} {'passed' if result else 'failed'}")
        passed_count += 1 if result else 0
    print("-" * 20)
    print(f"{passed_count} out of {len(test_file_names)} tests passed")
    os.system("rm testing/transpiled.cpp")
    set_running_tests_flag(False)


run_all_tests()
