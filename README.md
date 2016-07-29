# cRomanNumeralCalculator

cRomanNumeralCalculator is a roman numeral calculator written in C.

  - simple
  - pthreads, libcheck are the only dependencies

## Version
0.1.0

## Building

### Standalone Application:
```sh
$ make
```

#### Unit Tests:
```sh
$ make tests
```

Test binary will be built in the tests directory


## Running

```c
./cRomanNumeralCalculator MMMMCMXCIX XCIX add
<MMMMCMXCIX> + <XCIX> = <MMMMMXCVIII>

./cRomanNumeralCalculator MMMMCMXCIX XCIX subtract
<MMMMCMXCIX> - <XCIX> = <MMMMCM>
```


## Development

Ongoing

License
----

MIT
