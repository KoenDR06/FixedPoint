import os

if __name__ == "__main__":
    tests = []
    for (root,dirs,files) in os.walk('src/tests', topdown=True):
        for file in files:
            tests.append(f"{root}/{file}")

    with open("generated_tests.cmake", "w") as f:
        for test in tests:
            testName = "TEST_" + test.split(".")[0].replace("/", "_")

            f.write(
f"""add_executable(
        {testName}
        src/FixedPoint.h
        {test}
)
add_test(NAME urmom COMMAND {testName})\n\n""")
