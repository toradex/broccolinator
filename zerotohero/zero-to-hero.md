---
customTheme: "torizon"
transition: "none"
highlightTheme: "monokai"
logoImg: "torizon_white.png"
slideNumber: true
title: "From Zero to Hero"
---

# From Zero to Hero

## Visual Studio Code for Embedded Linux Development

---

# Poll

---

## Visual Studio Code

- editor on steroids
- [very popular development environment](https://insights.stackoverflow.com/survey/2019#development-environments-and-tools)
- extensible

---

| Visual Studio            | Visual Studio Code                  |
|--------------------------|-------------------------------------|
| IDE                      | Editor                              |
| Windows Only             | Multi-platform                      |
| Has his own build system | Can support different build systems |
| Closed source            | Open Source                         |
| Microsoft driven         | Community driven                    |

---

## Torizon and VSCode

- Productive development environment
- [Torizon extension](https://marketplace.visualstudio.com/items?itemName=Toradex.torizon)

---

# Poll

---

## Torizon extension

---

## Supported languages/frameworks

- Python
- .NET Core
    - C#
    - console and ASP .NET
- C/C++
    - different build systems
    - Qt5

---

# Poll

---

## How can I create a Torizon application in Visual Studio Code?

---

![flow](./flow.svg =300x600)

---

## Python

- support remote debugging
- support package installation via pip and/or debian
- support for Qt for Python

---

# Poll

---

## .NET Core

- must have .NET SDK installed
- ASP .NET and .NET Core
- support for nuget packages

---

# Poll

---

## C/C++

- uses SDK container for the toolchain
- supports different build systems
    - makefile
    - automake
    - cmake
    - qmake

---

## Qt

- support for Qt5 from debian
- support for Qt designer
- QML/Widgets UI

---

## Configure a project

- platforms
- application configuration

---

## Under the hood

- containers
- debug/release
- fast debug cycle

---

# Broccolinator

---

## Broccolinator

- multiple containers
- different languages
- [open source](https://github.com/toradex/broccolinator)

![broccolinator](broccolinator.png =600x400)

---

# Extreme debugging!

---

## Deploy your application

- build release container
- publish container
- deploy using OTA

---
