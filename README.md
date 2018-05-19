Snicker
===

[![CodeFactor](https://www.codefactor.io/repository/github/misterbianco/snicker/badge)](https://www.codefactor.io/repository/github/misterbianco/snicker)
[![Build Status](https://travis-ci.org/MisterBianco/Snicker.svg?branch=master)](https://travis-ci.org/MisterBianco/Snicker)

Snicker is a high performance packet sniffer written in C++

This is mostly a personal project and is subject to major changes and is currently unstable.

Benchmarks are coming...

State: Testing

Usage:
---

```
    git clone https://github.com/MisterBianco/Snicker
    cd Snicker
    sudo chmod +x setup.sh && ./setup.sh
    make
    cd build
    sudo snicker -i [wireless name]
```

Running Tests:
---

```
    cd source/tests
    make check
```

Eventually I plan to collapse all this to a single make file

Contributing
---

Please submit bug reports and pull requests, I will get to them as I am able.
