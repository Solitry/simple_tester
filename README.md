# An lecture tester

---

## How to use

Make sure your PC has python3. (3.6 ~ 3.11 are all OK with this tester)

Create a folder for your c programming project and put the tester.py under this folder.

Inside this folder, you can create a sub-folder for each lexture,
and put your source code in it.

And next, we create test data for the code (e.g. `input0.txt` and `output0.txt`).
`input0.txt` is an input to your code, and the `output0.txt` is the output that we expect.

Of cource, we can give more than 1 pair of input and output, with different name suffix.
e.g. `input1.txt` and `output1.txt`.


And the top-level folder will be like this:

```
c_project/
|- lecture0/
|   |- main.c
|   |- input0.txt
|   |- output0.txt
|   |- input1.txt
|   |- output1.txt
|- tester.py
```

And in the `c_project/` folder, run:

```python
python3 tester.py lecture0 main.c
```

The tester will compile the `main.c`, and run it with `input0.txt` and `input1.txt`.
And the tester will compare the output with the `output0.txt` and `output1.txt`.
If there is any error, the tester will report it.
