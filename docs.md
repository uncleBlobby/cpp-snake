# CPP Libraries

## httplib.h
https://github.com/yhirose/cpp-httplib

## json.jpp
https://github.com/nlohmann/json

Sample json object creation:

json ex1 = json::parse(R"(
  {
    "pi": 3.141,
    "happy": true
  }
)");

# API REQUESTS

## GET /

Empty get request made to the top level url.

Response shape:

```json
{
  "apiversion": "1",
  "author": "MyUsername",
  "color": "#888888",
  "head": "default",
  "tail": "default",
  "version": "0.0.1-beta"
}
```