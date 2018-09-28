local cputime = require 'cputime'

local utime1, stime1, cutime1, cstime1, err = cputime.get_cputime()
if err ~= nil then
    print(err)
    os.exit(1)
end

local buf = ''
for i=0,500000 do
    buf = buf .. '*'
end

local utime2, stime2, cutime2, cstime2, err = cputime.get_cputime()
if err ~= nil then
    print(err)
    os.exit(1)
end

print('utime: ' .. utime2 - utime1)
print('stime: ' .. stime2 - stime1)
print('cutime: ' .. cutime2 - cutime1)
print('cstime: ' .. cstime2 - cstime1)
