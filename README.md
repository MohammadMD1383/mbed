# mbed
lets you embed any file in a c/c++ program using a generated header file

### `mbed --help`
```
+--------------------------------------------+
|               --<* MBed *>--               |
| lets you embed any file in a c/c++ program |
|       using a generated header file.       |
+--------------------------------------------+

Options:
  -i [ --input ] arg        file(s) to generate embeddable data for
  -o [ --output ] arg       output name for '.c' and '.h' files
  -g [ --header-guard ] arg name of the header guard for the generated '.h' 
                            file
  -H [ --header-only ]      produce only a header file (without a '.c' source 
                            file
  -s [ --stdin ]            read data from stdin and output to stdout if the 
                            <output> arg is not specified
  -S [ --stdout ]           output generated data to stdout even if the 
                            <output> arg is present
  -c [ --chars-only ]       output only generated characters instead of a 'c' 
                            file content
  -h [ --help ]             print this help message
  -e [ --examples ]         print examples
```

### `mbed --examples`
```
----<|[MBED | EXAMPLES]|>----

*) GENERATE FROM FILE(s) TO FILE
  + mbed <[--output,-o] output-name> <[--input,-i] input-files...> [--header-only,-H]
    - mbed -i img1.png img2.png -o images -H
      This will generate 'mbed_images.h' with the following
      const variables:
        const char img1[] = {...};
        const char img2[] = {...};

    - mbed mJarFile a.jar
      This will generate 'mbed_mJarFile.{c,h}' and will
      contain the following const variable:
        extern const char mJarFile[];


*) GENERATE FROM STDIN TO FILE
  + mbed <--stdin,-s> <[--output,-o] output-name> <[--input,-i] input-name> [--header-only,-H]
    - mbed -si bin_var -o bin < img.png
      This will generate 'mbed_bin_var.{c,h}' with the following
      const variable:
        extern const char bin_var[];

    - cat someImage.png | mbed -sH image myImage
      This will generate 'mbed_image.h' and will
      contain the following const variable:
        const char image[] = {...};


*) GENERATE FROM STDIN TO STDOUT
  + mbed <--stdin,-s> <--stdout,-S> <[--input,-i] input-name> [--chars-only,-c]
    - cat lib.so | mbed -csS
      This will output the something like below to stdout:
        '\x0A','\x4B','\xCD',...


*) GENERATE FROM FILE(s) TO STDOUT
  + mbed <--stdout,-S> <[--input,-i] input-files...> [--chars-only,-c]
    - mbed -i lib.a -S
      This will output the something like below to stdout:
        #ifndef MBED__H
        #define MBED__H
        const char lib[] = {...};
        #endif


*) SPECIFY HEADER GUARD
  + mbed [options...] [--header-guard,-g <guard-name>]
    - mbed -i img.png -o bin-data -g BIN_DATA
      This will produce a 'mbed_bin-data.h' with the following content:
        #ifndef MBED_BIN_DATA_H
        #define MBED_BIN_DATA_H
        const char img[] = {...};
        #endif


*** TO SEE ALL POSSIBLE OPTIONS EXECUTE 'mbed -h' ***
```
