# ReadMe

The directory contains files to create a binary file using [`flatbuffers`](http://github.com/google/flatbuffers) using `C++` and reading the same file using `Python`.
## Files
* **Client.fbs:** Schema of the buffer.
* **fb_encoder.cpp:** C++ file to create flatbuffers and store in a binary file.
* **fb_decoder.py:** Python file to read the flatbuffer from the binary file.

## Prerequisited
* Build the flatbuffer. You can go throught the basic [tutorrial](https://google.github.io/flatbuffers/flatbuffers_guide_tutorial.html)
* Create a `venv` to install `flatbuffers` for python.

## Steps to execute the code
* Use the flatbuffer compiler to compile the schema

    `flatc --cpp Client.fbs`
    
    `flatc --python Client.fbs`
* Run the `fb_encode.cpp` file, don't forget to include the path of flatbuffers header file.

    `g++ -I/flatbuffers/include fb_encoder.cpp`
    
    `./a.out`
* After running the above two commands, you can see a new `fb_bytes.bin` in same directory. This is the file which contains your binary data.
* Assuming that you have activated your `venv` run `fb_decode.py`

    `python fb_decode.py`
* Output is on your screen.
