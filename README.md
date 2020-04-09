<!--
***
*** To avoid retyping too much info. Do a search and replace for the following:
*** dev-env-cpp, twitter_handle, email
-->

<!-- PROJECT SHIELDS -->
<!--
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
![Build][build-shield]

<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/EOEPCA/proc_comm_lib_argo">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">proc_comm_lib_argo</h3>

  <p align="center">
    Tools and environment definitions for local EOEPCA service development activities for C++
    <br />
    <a href="https://github.com/EOEPCA/dev-env-cpp"><strong>Explore the docs »</strong></a>
    <br />
    <a href="https://github.com/EOEPCA/dev-env-cpp">View Demo</a>
    ·
    <a href="https://github.com/EOEPCA/dev-env-cpp/issues">Report Bug</a>
    ·
    <a href="https://github.com/EOEPCA/dev-env-cpp/issues">Request Feature</a>
  </p>
</p>

<!-- TABLE OF CONTENTS -->

## Table of Contents

- [Table of Contents](#table-of-contents)
- [About The Project](#about-the-project)
  - [Built With](#built-with)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
- [License](#license)

<!-- ABOUT THE PROJECT -->

## About The Project

 *proc_comm_lib_argo* is a shared library to provides the means to be able to create and submit Argo Workflows.

### Built With

- [CMAKE](https://cmake.org/)
- [googletest](https://github.com/google/googletest)


### Prerequisites

Before you start, you should already have the following softwares installed:

- [Vagrant](https://www.vagrantup.com/docs/installation/)
- [VirtualBox](https://www.virtualbox.org/manual/ch02.html)

To compile the library, a compiler that supports C++[14](https://en.cppreference.com/w/cpp/14)/[17](https://en.cppreference.com/w/cpp/17) is required.

EOEPCA team provides a ready-made Docker Image

```shel
docker pull eoepca/eoepca-build-cpp:1.0
```

If you want to create the Docker image yourself, the repository provides a Docker file to satisfy all requests (Dockerfile_builder)

```bash
docker build -t eoepca-build-cpp:1.0 -f Dockerfile_builder
```


## Getting Started

To get a local copy up and running follow these simple steps.

### Prerequisites

- [Docker](https://www.docker.com/)
- [Linux bash](https://en.wikipedia.org/wiki/Bash_(Unix_shell))

### Installation

1. Clone the repo

```sh
git clone https://github.com/EOEPCA/proc-comm-lib-argo.git
```

2. Change local directory

```sh
cd cd proc-comm-lib-argo
```

For this example we'll use the ready-made Docker Image `eoepca/eoepca-build-cpp:1.0`

3. Build application

Let's prepare the environment variables

```shell
export LOCAL_DOCKERIMAGE='eoepca/eoepca-build-cpp:1.0'
export CMAKERELEASE='Release'
```

Prepare the makefile

```shel
docker run --rm -ti  -v $PWD:/project/ -w /project/build/  ${LOCAL_DOCKERIMAGE} cmake -DCMAKE_BUILD_TYPE=${CMAKERELEASE} -G "CodeBlocks - Unix Makefiles" ..
```

... and make

```shel
docker run --rm -ti  -v $PWD:/project/ -w /project/build/  ${LOCAL_DOCKERIMAGE} make
```

list directory

```shell
ls -ltr build/
```

expected results:

```shell
[qbert@mycase proc-comm-lib-argo]$ ls -ltr build/
total 476
drwxr-xr-x 3 root root   4096 apr  9 11:36 3ty
-rw-r--r-- 1 root root    236 apr  9 11:36 yaml-cpp.pc
-rw-r--r-- 1 root root  52293 apr  9 11:37 CMakeCache.txt
-rw-r--r-- 1 root root  14579 apr  9 11:37 Makefile
-rw-r--r-- 1 root root   1702 apr  9 11:37 cmake_install.cmake
drwxr-xr-x 2 root root   4096 apr  9 11:37 bin
-rw-r--r-- 1 root root  49518 apr  9 11:37 proc_comm_lib_argo.cbp
-rwxr-xr-x 1 root root 301832 apr  9 11:38 libeoepcaargo.so
-rwxr-xr-x 1 root root  25000 apr  9 11:38 proc_comm_lib_argo
drwxr-xr-x 2 root root   4096 apr  9 11:38 lib
drwxr-xr-x 2 root root   4096 apr  9 11:42 build
drwxr-xr-x 6 root root   4096 apr  9 11:42 tests
drwxr-xr-x 6 root root   4096 apr  9 11:42 CMakeFiles

```

The library has been created `libeoepcaargo.so`

### Testing

#### Prerequisites

- [LibXml2](http://xmlsoft.org/)
- [LibXslt](http://xmlsoft.org/)

from the root of the repository

```shell
 ./build/tests/libtest-test --gtest_break_on_failure
```

runs only the unit tests

## Documentation

The component documentation can be found at https://github.com/EOEPCA/proc-comm-lib-argo/


<!-- LICENSE -->

## License

Distributed under the Apache-2.0 License. See `LICENSE` for more information.

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->

[contributors-shield]: https://img.shields.io/github/contributors/EOEPCA/template-svce.svg?style=flat-square
[contributors-url]: https://github.com/EOEPCA/template-svce/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/EOEPCA/template-svce.svg?style=flat-square
[forks-url]: https://github.com/EOEPCA/template-svce/network/members
[stars-shield]: https://img.shields.io/github/stars/EOEPCA/template-svce.svg?style=flat-square
[stars-url]: https://github.com/EOEPCA/template-svce/stargazers
[issues-shield]: https://img.shields.io/github/issues/EOEPCA/template-svce.svg?style=flat-square
[issues-url]: https://github.com/EOEPCA/template-svce/issues
[license-shield]: https://img.shields.io/github/license/EOEPCA/template-svce.svg?style=flat-square
[license-url]: https://github.com/EOEPCA/template-svce/blob/master/LICENSE
[build-shield]: https://www.travis-ci.com/EOEPCA/template-svce.svg?branch=master
[product-screenshot]: images/screenshot.png
