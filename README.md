# Ray Tracing in One Weekend in V

![Output from ray tracing](/output.png)

This is a ray tracing implementation in C, pretty much a re-implementation of an [earlier attempt](https://github.com/shovon/raytracing-golang) in Go

All implementation was translated from the minibook _[Ray Tracing In One Weekend](https://www.amazon.ca/Ray-Tracing-Weekend-Minibooks-Book-ebook/dp/B01B5AODD8)_. The book opted for C++, but I figured it's a good way to give C a try.

## Running the ray tracer

```
make
./raytracer-c > img.ppm
```

The program outputs portable pixmap format to the console/stdout, and so, the `>` symbol writes the output to a file.

Rendering a whole 1024 by 576 image takes around an 5 to 6 minutes on my 2019 M1 MacBook Pro. If you want something rendered quicker, change the `nx` and `ny` variables in `main()`, in `main.c` to something smaller than 1024 by 576 (perhaps 200 and 100, respectively).
