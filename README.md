# memperf
Memory performance test written in Go.

# What does the test do?
The program test memory random write in a buffer memory for 1 million times. It tests from 4k size buffer (a page) to 1GB buffer.

# Results
Some interesting results using my own hardware and cloud VM:

![This is an image](/content/rand_write.png)
