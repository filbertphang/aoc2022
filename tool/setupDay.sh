#!/bin/bash

DAY=$1
YEAR=2022
DIRNAME=$( dirname -- "$0"; )

echo "Setting up files for Advent of Code ${YEAR}: Day ${DAY}..."
echo $DIRNAME
mkdir "../day${DAY}"

curl "https://adventofcode.com/2022/day/${DAY}/input" \
  -H 'authority: adventofcode.com' \
  -H 'accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9' \
  -H 'accept-language: en-GB-oxendict,en;q=0.9' \
  -H 'cache-control: max-age=0' \
  -H "cookie: session=$(< "$DIRNAME/session_cookie")" \
  -H 'dnt: 1' \
  -H 'referer: https://adventofcode.com/2022/day/3' \
  -H 'sec-ch-ua: "Microsoft Edge";v="107", "Chromium";v="107", "Not=A?Brand";v="24"' \
  -H 'sec-ch-ua-mobile: ?0' \
  -H 'sec-ch-ua-platform: "Windows"' \
  -H 'sec-fetch-dest: document' \
  -H 'sec-fetch-mode: navigate' \
  -H 'sec-fetch-site: same-origin' \
  -H 'sec-fetch-user: ?1' \
  -H 'upgrade-insecure-requests: 1' \
  -H 'user-agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/107.0.0.0 Safari/537.36 Edg/107.0.1418.62' \
  --compressed --silent --output "../day${DAY}/input" 
  
echo -e '#include <bits/stdc++.h>\nusing namespace std;\nint main() {\n    \n}' > "../day${DAY}/sol1.cpp"
echo "Done!"