# kprintf

A tiny journey through time — `printf` in the FreeBSD kernel.

## Overview

This repository contains kernel-space `printf` implementations across two generations of FreeBSD.

- `freebsd4/`: for FreeBSD 4.x  
  _In 2002, I was young and I wanted to be a kernel hacker._  
  This directory contains code to perform `printf` within the FreeBSD 4 kernel.

- `freebsd14/`: for FreeBSD 14.x  
  _In 2025, I patched my memory._  
  This is a refreshed take on the same goal — `kprintf` for the modern kernel.

## Notes

Some dreams stay dormant.  
Others compile again — and do `RTFM`.
