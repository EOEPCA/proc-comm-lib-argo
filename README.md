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

 proc_comm_lib_argo is a shared library to provide to ADES Core the means to be able to create and submit Argo Workflows.

### Built With

- [CMAKE](https://cmake.org/)
- [googletest](https://github.com/google/googletest)


<!-- GETTING STARTED -->

## Getting Started

1. Download and install [VirtualBox](https://www.virtualbox.org/) 

2. Download and install the appropriate [Vagrant package for your OS](https://www.vagrantup.com/downloads.html).

3. Download EOEPCA development environment template for c++ 
    
<pre><code>   wget https://github.com/EOEPCA/dev-env-cpp/archive/develop.zip'</code></pre>

4. Build and instantiate the EOEPCA development environment

* Via CentOs GUI
 <pre><code>  DEV_DESKTOP=true vagrant up</code></pre>

* Via ssh

<pre><code>   vagrant up
   vagrant ssh</code></pre>

### Prerequisites

Before you start, you should already have the following softwares installed:

- [Vagrant](https://www.vagrantup.com/docs/installation/)
- [VirtualBox](https://www.virtualbox.org/manual/ch02.html)


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
