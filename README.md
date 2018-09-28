lua-cputime
==

A bridge library for CPU time measurement.

Synopsis
--

```lua
local cputime = require 'cputime'

local utime, stime, cutime, cstime, err = cputime.get_cputime()
if err ~= nil then
  -- error handling...
end
```

See also [example](/example/).

Description
--

This package provides a method to measure (and dispense) the CPU time.
The library bridges to `times()` function of `sys/times.h`.

Functions
--

### `get_cputime()`

This function returns the measured CPU time.

#### Return value

According the following order:

- utime (number or nil): user CPU time. This variable represents milliseconds.
- stime (number or nil): system CPU time. This variable represents milliseconds.
- cutime (number or nil): user CPU time of terminated child processes. This variable represents milliseconds.
- cstime (number or nil): system CPU time of terminated child processes. This variable represents milliseconds.
- err (string or nil): error response

When err is nil, other values are actual number value. On the other hand, when err is not nil, other values are nil.

Disclaimer
--

This library doesn't work on Windows (I have a will to support it).

See also
--

- http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_times.h.html

License
--

```
The MIT License (MIT)
Copyright © 2018 moznion, http://moznion.net/ <moznion@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the “Software”), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
```

