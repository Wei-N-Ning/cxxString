#!/usr/bin/env bash

sutbin=${1:?missing program}

# using the default delimiter (whitespace characters)

${sutbin} << "EOF"
# comment:
[/]project(doom)
[/]scene(e1)
[/]shot(m1)

# comment:
[/]element(archvile)
[/]product(motion)

[/]version(101)
[/]resource(apm)

EOF

# using [/] as the delimiter

${sutbin} '\[/\]' << "EOF"
# comment:
[/]project(doom)
[/]scene(e1)
[/]shot(m1)

# comment:
[/]element(archvile)
[/]product(motion)

[/]version(101)
[/]resource(apm)

EOF
