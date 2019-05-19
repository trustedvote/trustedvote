# Trusted Vote [![Gitter](https://badges.gitter.im/trustedvote/community.svg)](https://gitter.im/trustedvote/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)

This is s core of Trusted Vote system. It contains libtrustedvote, which is the core of Trusted Vote, daemon and CLI for daemon.

## Build requirements

- C++17 toolchain.
- GNU Autotools.
- GNU Automake.
- GNU Libtool.

## Dependencies

- Boost 1.69

## Build instructions

```sh
./autogen.sh
```

```sh
./configure
```

```sh
make
```

## Running tests

To run all unit tests, do:

```sh
make check
```

To run a specific unit test for libtrustedvote, do:

```sh
./src/libtrustedvote/libtrustedvote-test --run_test=SUITENAME/CASENAME
```
