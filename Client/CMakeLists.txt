cmake_minimum_required(VERSION 3.0.0)
project(app-client VERSION 0.1.0)

add_executable(appclient 
    IO.c
    main.c 
    USB.c
    dbg.c
    file_IO.c
)