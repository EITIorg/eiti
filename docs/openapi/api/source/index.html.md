Compiling all doT templates...
Loaded def authentication.def
Loaded def authentication_none.def
Loaded def callbacks.def
Loaded def debug.def
Loaded def discovery.def
Loaded def footer.def
Loaded def links.def
Loaded def parameters.def
Loaded def responses.def
Loaded def security.def
Compiling code_go.dot to function
Compiling code_http.dot to function
Compiling code_java.dot to function
Compiling code_javascript.dot to function
Compiling code_nodejs.dot to function
Compiling code_python.dot to function
Compiling code_ruby.dot to function
Compiling code_shell.dot to function
Compiling main.dot to function
Compiling operation.dot to function
Compiling translations.dot to function
---
title: EITI - API documentation v2.0
language_tabs:
  - shell: Shell
  - http: HTTP
  - javascript: JavaScript
  - javascript--nodejs: Node.JS
  - ruby: Ruby
  - python: Python
  - java: Java
  - go: Go
toc_footers: []
includes: []
search: true
highlight_theme: darkula
headingLevel: 2

---

<h1 id="EITI---API-documentation">EITI - API documentation v2.0</h1>

> Scroll down for code samples, example requests and responses. Select a language for code samples from the tabs above or the mobile navigation menu.

Eiti.org

Base URLs:

* <a href="https://eiti.org/api">https://eiti.org/api</a>

<h1 id="EITI---API-documentation-Country-Status-v1">Country Status v1</h1>

## get__v1.0_country_status

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/country_status \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/country_status HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/country_status',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/country_status',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/country_status',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/country_status', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/country_status");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/country_status", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/country_status`

Fetches all the country statuses defined in the system and returns them as JSON objects

<h3 id="get__v1.0_country_status-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|filter[color]|query|string|false|Allows to filter the country statuses by their color|

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "color": "string"
    }
  ],
  "count": 0,
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_country_status-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_country_status-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» color|string|false|No description|
|» count|integer|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

## get__v1.0_country_status_{id}

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/country_status/{id} \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/country_status/{id} HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/country_status/{id}',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/country_status/{id}',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/country_status/{id}',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/country_status/{id}', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/country_status/{id}");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/country_status/{id}", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/country_status/{id}`

Fetches a single country status defined in the system and returns it as a JSON object

<h3 id="get__v1.0_country_status_{id}-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|id|path|integer|false|No description|

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "color": "string"
    }
  ],
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_country_status_{id}-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_country_status_{id}-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» color|string|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

<h1 id="EITI---API-documentation-Country-Status-v2">Country Status v2</h1>

## get__v2.0_country_status

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v2.0/country_status \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v2.0/country_status HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v2.0/country_status',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v2.0/country_status',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v2.0/country_status',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v2.0/country_status', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v2.0/country_status");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v2.0/country_status", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v2.0/country_status`

Fetches all the country statuses defined in the system and returns them as JSON objects

<h3 id="get__v2.0_country_status-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|filter[color]|query|string|false|Allows to filter the country statuses by their color|

> Example responses

```json
{
  "data": [
    {
      "id": "string",
      "label": "string",
      "self": "string",
      "color": "string"
    }
  ],
  "count": 0,
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v2.0_country_status-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v2.0_country_status-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|string|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» color|string|false|No description|
|» count|integer|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

## get__v2.0_country_status_{id}

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v2.0/country_status/{id} \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v2.0/country_status/{id} HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v2.0/country_status/{id}',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v2.0/country_status/{id}',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v2.0/country_status/{id}',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v2.0/country_status/{id}', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v2.0/country_status/{id}");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v2.0/country_status/{id}", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v2.0/country_status/{id}`

Fetches a single country status defined in the system and returns it as a JSON object

<h3 id="get__v2.0_country_status_{id}-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|id|path|string|false|No description|

> Example responses

```json
{
  "data": [
    {
      "id": "string",
      "label": "string",
      "self": "string",
      "color": "string"
    }
  ],
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v2.0_country_status_{id}-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v2.0_country_status_{id}-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|string|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» color|string|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

<h1 id="EITI---API-documentation-GFS-Code-v1">GFS Code v1</h1>

## get__v1.0_gfs_code

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/gfs_code \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/gfs_code HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/gfs_code',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/gfs_code',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/gfs_code',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/gfs_code', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/gfs_code");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/gfs_code", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/gfs_code`

Fetches all the GFS codes defined in the system and returns them as JSON objects

<h3 id="get__v1.0_gfs_code-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|filter[code]|query|string|false|Allows to filter the GFS codes by their code|
|filter[parent]|query|string|false|Allows to filter the GFS codes by their parent|

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "code": "string",
      "parent": 0
    }
  ],
  "count": 0,
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_gfs_code-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_gfs_code-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» code|string|false|No description|
|»» parent|integer|false|No description|
|» count|integer|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

## get__v1.0_gfs_code_{id}

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/gfs_code/{id} \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/gfs_code/{id} HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/gfs_code/{id}',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/gfs_code/{id}',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/gfs_code/{id}',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/gfs_code/{id}', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/gfs_code/{id}");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/gfs_code/{id}", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/gfs_code/{id}`

Fetches a single GFS code defined in the system and returns it as a JSON object

<h3 id="get__v1.0_gfs_code_{id}-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|id|path|integer|false|No description|

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "code": "string",
      "parent": 0
    }
  ],
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_gfs_code_{id}-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_gfs_code_{id}-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» code|string|false|No description|
|»» parent|integer|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

<h1 id="EITI---API-documentation-GFS-Code-v2">GFS Code v2</h1>

## get__v2.0_gfs_code

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v2.0/gfs_code \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v2.0/gfs_code HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v2.0/gfs_code',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v2.0/gfs_code',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v2.0/gfs_code',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v2.0/gfs_code', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v2.0/gfs_code");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v2.0/gfs_code", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v2.0/gfs_code`

Fetches all the GFS codes defined in the system and returns them as JSON objects

<h3 id="get__v2.0_gfs_code-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|filter[code]|query|string|false|Allows to filter the GFS codes by their code|
|filter[parent]|query|string|false|Allows to filter the GFS codes by their parent|

> Example responses

```json
{
  "data": [
    {
      "id": "string",
      "label": "string",
      "self": "string",
      "code": "string",
      "parent": "string"
    }
  ],
  "count": 0,
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v2.0_gfs_code-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v2.0_gfs_code-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|string|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» code|string|false|No description|
|»» parent|string|false|No description|
|» count|integer|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

## get__v2.0_gfs_code_{id}

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v2.0/gfs_code/{id} \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v2.0/gfs_code/{id} HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v2.0/gfs_code/{id}',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v2.0/gfs_code/{id}',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v2.0/gfs_code/{id}',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v2.0/gfs_code/{id}', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v2.0/gfs_code/{id}");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v2.0/gfs_code/{id}", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v2.0/gfs_code/{id}`

Fetches a single GFS code defined in the system and returns it as a JSON object

<h3 id="get__v2.0_gfs_code_{id}-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|id|path|string|false|No description|

> Example responses

```json
{
  "data": [
    {
      "id": "string",
      "label": "string",
      "self": "string",
      "code": "string",
      "parent": "string"
    }
  ],
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v2.0_gfs_code_{id}-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v2.0_gfs_code_{id}-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|string|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» code|string|false|No description|
|»» parent|string|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

<h1 id="EITI---API-documentation-Implementing-Country-v1">Implementing Country v1</h1>

## get__v1.0_implementing_country

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/implementing_country \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/implementing_country HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/implementing_country',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/implementing_country',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/implementing_country',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/implementing_country', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/implementing_country");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/implementing_country", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/implementing_country`

Fetches all of the implementing countries and shows them as JSON objects

<h3 id="get__v1.0_implementing_country-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|filter[iso2]|query|string|false|Allows to filter implementing countries by their ISO2 code|
|filter[status]|query|string|false|Allows to filter implementing countries by their status tid|
|filter[status_date]|query|string|false|Allows to filter implementing countries by their status date in YYYY-MM-DD format|
|filter[leave_date]|query|string|false|Allows to filter implementing countries by their leaving date in YYYY-MM-DD format|
|filter[local_website]|query|string|false|Allows to filter implementing countries by their local_website url|
|filter[annual_report_file]|query|string|false|Allows to filter implementing countries by their annual report file fid|
|filter[latest_validation_date]|query|string|false|Allows to filter implementing countries by their latest validation date in YYYY-MM-DD (YYYY-01-01) format|
|filter[latest_validation_link]|query|string|false|Allows to filter implementing countries by their latest validation link id|
|filter[latest_validation_url]|query|string|false|Allows to filter implementing countries by their latest validation url|

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "iso2": "string",
      "iso3": "string",
      "status": {
        "tid": 0,
        "language": "string",
        "name": "string",
        "color": "string"
      },
      "status_date": 0,
      "local_website": "string",
      "annual_report_file": "string",
      "reports": {
        "property1": [
          {
            "commodity": "string",
            "parent": "string",
            "id": 0,
            "value": 0,
            "value_bool": 0,
            "value_text": "string",
            "unit": "string",
            "source": "string"
          }
        ],
        "property2": [
          {
            "commodity": "string",
            "parent": "string",
            "id": 0,
            "value": 0,
            "value_bool": 0,
            "value_text": "string",
            "unit": "string",
            "source": "string"
          }
        ]
      },
      "metadata": {
        "property1": {
          "contact": {
            "name": "string",
            "email": "string",
            "organisation": "string"
          },
          "year_start": "string",
          "year_end": "string",
          "currency_rate": 0,
          "currency_code": "string",
          "sectors_covered": [
            "string"
          ],
          "reporting_organisations": {
            "companies": 0,
            "governmental_agencies": 0
          },
          "web_report_links": [
            {
              "url": "string",
              "title": "string",
              "attributes": []
            }
          ],
          "disaggregated": {
            "project": 0,
            "revenue_stream": 0,
            "company": 0
          }
        },
        "property2": {
          "contact": {
            "name": "string",
            "email": "string",
            "organisation": "string"
          },
          "year_start": "string",
          "year_end": "string",
          "currency_rate": 0,
          "currency_code": "string",
          "sectors_covered": [
            "string"
          ],
          "reporting_organisations": {
            "companies": 0,
            "governmental_agencies": 0
          },
          "web_report_links": [
            {
              "url": "string",
              "title": "string",
              "attributes": []
            }
          ],
          "disaggregated": {
            "project": 0,
            "revenue_stream": 0,
            "company": 0
          }
        }
      },
      "licenses": {
        "property1": {
          "property1": "string",
          "property2": "string"
        },
        "property2": {
          "property1": "string",
          "property2": "string"
        }
      },
      "contracts": {
        "property1": {
          "property1": "string",
          "property2": "string"
        },
        "property2": {
          "property1": "string",
          "property2": "string"
        }
      },
      "revenues": {
        "property1": {
          "government": 0,
          "company": 0
        },
        "property2": {
          "government": 0,
          "company": 0
        }
      },
      "latest_validation_date": "string",
      "latest_validation_link": "string",
      "latest_validation_url": "string"
    }
  ],
  "count": 0,
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_implementing_country-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_implementing_country-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» iso2|string|false|No description|
|»» iso3|string|false|No description|
|»» status|object|false|No description|
|»»» tid|integer|false|No description|
|»»» language|string|false|No description|
|»»» name|string|false|No description|
|»»» color|string|false|No description|
|»» status_date|integer|false|No description|
|»» local_website|string|false|No description|
|»» annual_report_file|string|false|No description|
|»» reports|object|false|No description|
|»»» **additionalProperties**|[object]|false|No description|
|»»»» commodity|string|false|No description|
|»»»» parent|string|false|No description|
|»»»» id|integer|false|No description|
|»»»» value|integer|false|No description|
|»»»» value_bool|integer|false|No description|
|»»»» value_text|string|false|No description|
|»»»» unit|string|false|No description|
|»»»» source|string|false|No description|
|»»» metadata|object|false|No description|
|»»»» **additionalProperties**|object|false|No description|
|»»»»» contact|object|false|No description|
|»»»»»» name|string|false|No description|
|»»»»»» email|string|false|No description|
|»»»»»» organisation|string|false|No description|
|»»»»» year_start|string|false|No description|
|»»»»» year_end|string|false|No description|
|»»»»» currency_rate|number|false|No description|
|»»»»» currency_code|string|false|No description|
|»»»»» sectors_covered|[string]|false|No description|
|»»»»» reporting_organisations|object|false|No description|
|»»»»»» companies|integer|false|No description|
|»»»»»» governmental_agencies|integer|false|No description|
|»»»»» web_report_links|[object]|false|No description|
|»»»»»» url|string|false|No description|
|»»»»»» title|string|false|No description|
|»»»»»» attributes|array|false|No description|
|»»»»» disaggregated|object|false|No description|
|»»»»»» project|integer|false|No description|
|»»»»»» revenue_stream|integer|false|No description|
|»»»»»» company|integer|false|No description|
|»»»»» licenses|object|false|No description|
|»»»»»» **additionalProperties**|object|false|No description|
|»»»»»»» **additionalProperties**|string|false|No description|
|»»»»»» contracts|object|false|No description|
|»»»»»»» **additionalProperties**|object|false|No description|
|»»»»»»»» **additionalProperties**|string|false|No description|
|»»»»»»» revenues|object|false|No description|
|»»»»»»»» **additionalProperties**|object|false|No description|
|»»»»»»»»» government|integer|false|No description|
|»»»»»»»»» company|integer|false|No description|
|»»»»»»»» latest_validation_date|string|false|No description|
|»»»»»»»» latest_validation_link|string|false|No description|
|»»»»»»»» latest_validation_url|string|false|No description|
|»»»»»»» count|integer|false|No description|
|»»»»»»» self|object|false|No description|
|»»»»»»»» title|string|false|No description|
|»»»»»»»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

## get__v1.0_implementing_country_{id}

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/implementing_country/{id} \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/implementing_country/{id} HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/implementing_country/{id}',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/implementing_country/{id}',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/implementing_country/{id}',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/implementing_country/{id}', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/implementing_country/{id}");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/implementing_country/{id}", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/implementing_country/{id}`

Fetches a single implementing country and shows it as JSON object

<h3 id="get__v1.0_implementing_country_{id}-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|id|path|integer|false|No description|

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "iso2": "string",
      "iso3": "string",
      "status": {
        "tid": 0,
        "language": "string",
        "name": "string",
        "color": "string"
      },
      "status_date": 0,
      "local_website": "string",
      "annual_report_file": "string",
      "reports": {
        "property1": [
          {
            "commodity": "string",
            "parent": "string",
            "id": 0,
            "value": 0,
            "value_bool": 0,
            "value_text": "string",
            "unit": "string",
            "source": "string"
          }
        ],
        "property2": [
          {
            "commodity": "string",
            "parent": "string",
            "id": 0,
            "value": 0,
            "value_bool": 0,
            "value_text": "string",
            "unit": "string",
            "source": "string"
          }
        ]
      },
      "metadata": {
        "property1": {
          "contact": {
            "name": "string",
            "email": "string",
            "organisation": "string"
          },
          "year_start": "string",
          "year_end": "string",
          "currency_rate": 0,
          "currency_code": "string",
          "sectors_covered": [
            "string"
          ],
          "reporting_organisations": {
            "companies": 0,
            "governmental_agencies": 0
          },
          "web_report_links": [
            {
              "url": "string",
              "title": "string",
              "attributes": []
            }
          ],
          "disaggregated": {
            "project": 0,
            "revenue_stream": 0,
            "company": 0
          }
        },
        "property2": {
          "contact": {
            "name": "string",
            "email": "string",
            "organisation": "string"
          },
          "year_start": "string",
          "year_end": "string",
          "currency_rate": 0,
          "currency_code": "string",
          "sectors_covered": [
            "string"
          ],
          "reporting_organisations": {
            "companies": 0,
            "governmental_agencies": 0
          },
          "web_report_links": [
            {
              "url": "string",
              "title": "string",
              "attributes": []
            }
          ],
          "disaggregated": {
            "project": 0,
            "revenue_stream": 0,
            "company": 0
          }
        }
      },
      "licenses": {
        "property1": {
          "property1": "string",
          "property2": "string"
        },
        "property2": {
          "property1": "string",
          "property2": "string"
        }
      },
      "contracts": {
        "property1": {
          "property1": "string",
          "property2": "string"
        },
        "property2": {
          "property1": "string",
          "property2": "string"
        }
      },
      "revenues": {
        "property1": {
          "government": 0,
          "company": 0
        },
        "property2": {
          "government": 0,
          "company": 0
        }
      },
      "latest_validation_date": "string",
      "latest_validation_link": "string",
      "latest_validation_url": "string"
    }
  ],
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_implementing_country_{id}-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_implementing_country_{id}-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» iso2|string|false|No description|
|»» iso3|string|false|No description|
|»» status|object|false|No description|
|»»» tid|integer|false|No description|
|»»» language|string|false|No description|
|»»» name|string|false|No description|
|»»» color|string|false|No description|
|»» status_date|integer|false|No description|
|»» local_website|string|false|No description|
|»» annual_report_file|string|false|No description|
|»» reports|object|false|No description|
|»»» **additionalProperties**|[object]|false|No description|
|»»»» commodity|string|false|No description|
|»»»» parent|string|false|No description|
|»»»» id|integer|false|No description|
|»»»» value|integer|false|No description|
|»»»» value_bool|integer|false|No description|
|»»»» value_text|string|false|No description|
|»»»» unit|string|false|No description|
|»»»» source|string|false|No description|
|»»» metadata|object|false|No description|
|»»»» **additionalProperties**|object|false|No description|
|»»»»» contact|object|false|No description|
|»»»»»» name|string|false|No description|
|»»»»»» email|string|false|No description|
|»»»»»» organisation|string|false|No description|
|»»»»» year_start|string|false|No description|
|»»»»» year_end|string|false|No description|
|»»»»» currency_rate|number|false|No description|
|»»»»» currency_code|string|false|No description|
|»»»»» sectors_covered|[string]|false|No description|
|»»»»» reporting_organisations|object|false|No description|
|»»»»»» companies|integer|false|No description|
|»»»»»» governmental_agencies|integer|false|No description|
|»»»»» web_report_links|[object]|false|No description|
|»»»»»» url|string|false|No description|
|»»»»»» title|string|false|No description|
|»»»»»» attributes|array|false|No description|
|»»»»» disaggregated|object|false|No description|
|»»»»»» project|integer|false|No description|
|»»»»»» revenue_stream|integer|false|No description|
|»»»»»» company|integer|false|No description|
|»»»»» licenses|object|false|No description|
|»»»»»» **additionalProperties**|object|false|No description|
|»»»»»»» **additionalProperties**|string|false|No description|
|»»»»»» contracts|object|false|No description|
|»»»»»»» **additionalProperties**|object|false|No description|
|»»»»»»»» **additionalProperties**|string|false|No description|
|»»»»»»» revenues|object|false|No description|
|»»»»»»»» **additionalProperties**|object|false|No description|
|»»»»»»»»» government|integer|false|No description|
|»»»»»»»»» company|integer|false|No description|
|»»»»»»»» latest_validation_date|string|false|No description|
|»»»»»»»» latest_validation_link|string|false|No description|
|»»»»»»»» latest_validation_url|string|false|No description|
|»»»»»»» self|object|false|No description|
|»»»»»»»» title|string|false|No description|
|»»»»»»»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

<h1 id="EITI---API-documentation-Implementing-Country-v2">Implementing Country v2</h1>

## get__v2.0_implementing_country

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v2.0/implementing_country \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v2.0/implementing_country HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v2.0/implementing_country',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v2.0/implementing_country',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v2.0/implementing_country',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v2.0/implementing_country', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v2.0/implementing_country");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v2.0/implementing_country", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v2.0/implementing_country`

Fetches all of the implementing countries and shows them as JSON objects

<h3 id="get__v2.0_implementing_country-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|filter[iso2]|query|string|false|Allows to filter implementing countries by their ISO2 code|
|filter[status]|query|string|false|Allows to filter implementing countries by their status id|
|filter[join_date]|query|string|false|Allows to filter implementing countries by their joining date in YYYY-MM-DD format|
|filter[leave_date]|query|string|false|Allows to filter implementing countries by their leaving date in YYYY-MM-DD format|
|filter[local_website]|query|string|false|Allows to filter implementing countries by their local_website url|
|filter[annual_report_file]|query|string|false|Allows to filter implementing countries by their annual report file fid|

> Example responses

```json
{
  "data": [
    {
      "id": "string",
      "label": "string",
      "self": "string",
      "iso2": "string",
      "iso3": "string",
      "status": "string",
      "join_date": "string",
      "leave_date": "string",
      "local_website": "string",
      "annual_report_file": "string",
      "latest_validation_date": "string",
      "validation_data": [
        "string"
      ],
      "summary_data": [
        "string"
      ]
    }
  ],
  "count": 0,
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v2.0_implementing_country-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v2.0_implementing_country-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|string|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» iso2|string|false|No description|
|»» iso3|string|false|No description|
|»» status|string|false|No description|
|»» join_date|string|false|No description|
|»» leave_date|string|false|No description|
|»» local_website|string|false|No description|
|»» annual_report_file|string|false|No description|
|»» latest_validation_date|string|false|No description|
|»» validation_data|[string]|false|No description|
|»» summary_data|[string]|false|No description|
|» count|integer|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

## get__v2.0_implementing_country_{id}

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v2.0/implementing_country/{id} \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v2.0/implementing_country/{id} HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v2.0/implementing_country/{id}',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v2.0/implementing_country/{id}',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v2.0/implementing_country/{id}',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v2.0/implementing_country/{id}', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v2.0/implementing_country/{id}");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v2.0/implementing_country/{id}", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v2.0/implementing_country/{id}`

Fetches a single implementing country and shows it as JSON object

<h3 id="get__v2.0_implementing_country_{id}-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|id|path|string|false|No description|

> Example responses

```json
{
  "data": [
    {
      "id": "string",
      "label": "string",
      "self": "string",
      "iso2": "string",
      "iso3": "string",
      "status": "string",
      "join_date": "string",
      "leave_date": "string",
      "local_website": "string",
      "annual_report_file": "string",
      "latest_validation_date": "string",
      "validation_data": [
        "string"
      ],
      "summary_data": [
        "string"
      ]
    }
  ],
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v2.0_implementing_country_{id}-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v2.0_implementing_country_{id}-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|string|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» iso2|string|false|No description|
|»» iso3|string|false|No description|
|»» status|string|false|No description|
|»» join_date|string|false|No description|
|»» leave_date|string|false|No description|
|»» local_website|string|false|No description|
|»» annual_report_file|string|false|No description|
|»» latest_validation_date|string|false|No description|
|»» validation_data|[string]|false|No description|
|»» summary_data|[string]|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

<h1 id="EITI---API-documentation-Indicator-v1">Indicator v1</h1>

## get__v1.0_indicator

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/indicator \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/indicator HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/indicator',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/indicator',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/indicator',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/indicator', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/indicator");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/indicator", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/indicator`

Fetches all of the defined indicators and shows them as JSON objects

<h3 id="get__v1.0_indicator-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|filter[type]|query|string|false|Allows to filter indicators by their type|
|filter[parent]|query|string|false|Allows to filter indicators by their parent|
|filter[status]|query|string|false|Allows to filter indicators by their status|
|filter[created]|query|string|false|Allows to filter indicators by their created UNIX timestamp|

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "type": "string",
      "parent": 0,
      "status": 0,
      "created": 0
    }
  ],
  "count": 0,
  "self": {
    "title": "string",
    "href": "string"
  },
  "next": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_indicator-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_indicator-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» type|string|false|No description|
|»» parent|integer|false|No description|
|»» status|integer|false|No description|
|»» created|integer|false|No description|
|» count|integer|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|
|» next|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

## get__v1.0_indicator_{id}

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/indicator/{id} \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/indicator/{id} HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/indicator/{id}',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/indicator/{id}',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/indicator/{id}',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/indicator/{id}', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/indicator/{id}");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/indicator/{id}", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/indicator/{id}`

Fetches a single indicator and shows it as a JSON object

<h3 id="get__v1.0_indicator_{id}-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|id|path|integer|false|No description|

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "type": "string",
      "parent": 0,
      "status": 0,
      "created": 0
    }
  ],
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_indicator_{id}-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_indicator_{id}-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» type|string|false|No description|
|»» parent|integer|false|No description|
|»» status|integer|false|No description|
|»» created|integer|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

<h1 id="EITI---API-documentation-Indicator-v2">Indicator v2</h1>

## get__v2.0_indicator

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v2.0/indicator \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v2.0/indicator HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v2.0/indicator',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v2.0/indicator',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v2.0/indicator',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v2.0/indicator', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v2.0/indicator");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v2.0/indicator", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v2.0/indicator`

Fetches all of the defined indicators and shows them as JSON objects

<h3 id="get__v2.0_indicator-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|filter[type]|query|string|false|Allows to filter indicators by their type|
|filter[parent]|query|string|false|Allows to filter indicators by their parent|

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "type": "string",
      "parent": 0
    }
  ],
  "count": 0,
  "self": {
    "title": "string",
    "href": "string"
  },
  "next": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v2.0_indicator-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v2.0_indicator-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» type|string|false|No description|
|»» parent|integer|false|No description|
|» count|integer|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|
|» next|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

## get__v2.0_indicator_{id}

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v2.0/indicator/{id} \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v2.0/indicator/{id} HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v2.0/indicator/{id}',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v2.0/indicator/{id}',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v2.0/indicator/{id}',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v2.0/indicator/{id}', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v2.0/indicator/{id}");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v2.0/indicator/{id}", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v2.0/indicator/{id}`

Fetches a single indicator and shows it as a JSON object

<h3 id="get__v2.0_indicator_{id}-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|id|path|integer|false|No description|

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "type": "string",
      "parent": 0
    }
  ],
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v2.0_indicator_{id}-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v2.0_indicator_{id}-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» type|string|false|No description|
|»» parent|integer|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

<h1 id="EITI---API-documentation-Indicator-Values-v1">Indicator Values v1</h1>

## get__v1.0_indicator_value

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/indicator_value \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/indicator_value HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/indicator_value',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/indicator_value',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/indicator_value',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/indicator_value', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/indicator_value");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/indicator_value", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/indicator_value`

Fetches all the indicator values and their details as JSON objects

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "value": 0,
      "unit": "string",
      "indicator": {
        "id": 0,
        "type": "string",
        "name": "string",
        "pranet": 0,
        "status": 0,
        "created": 0
      }
    }
  ],
  "count": 0,
  "self": {
    "title": "string",
    "href": "string"
  },
  "next": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_indicator_value-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_indicator_value-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» value|integer|false|No description|
|»» unit|string|false|No description|
|»» indicator|object|false|No description|
|»»» id|integer|false|No description|
|»»» type|string|false|No description|
|»»» name|string|false|No description|
|»»» pranet|integer|false|No description|
|»»» status|integer|false|No description|
|»»» created|integer|false|No description|
|»» count|integer|false|No description|
|»» self|object|false|No description|
|»»» title|string|false|No description|
|»»» href|string|false|No description|
|»» next|object|false|No description|
|»»» title|string|false|No description|
|»»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

## get__v1.0_indicator_value_{id}

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/indicator_value/{id} \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/indicator_value/{id} HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/indicator_value/{id}',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/indicator_value/{id}',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/indicator_value/{id}',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/indicator_value/{id}', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/indicator_value/{id}");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/indicator_value/{id}", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/indicator_value/{id}`

Fetches a single indicator value and its details as a JSON object

<h3 id="get__v1.0_indicator_value_{id}-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|id|path|integer|false|No description|

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "value": 0,
      "unit": "string",
      "indicator": {
        "id": 0,
        "type": "string",
        "name": "string",
        "pranet": 0,
        "status": 0,
        "created": 0
      }
    }
  ],
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_indicator_value_{id}-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_indicator_value_{id}-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» value|integer|false|No description|
|»» unit|string|false|No description|
|»» indicator|object|false|No description|
|»»» id|integer|false|No description|
|»»» type|string|false|No description|
|»»» name|string|false|No description|
|»»» pranet|integer|false|No description|
|»»» status|integer|false|No description|
|»»» created|integer|false|No description|
|»» self|object|false|No description|
|»»» title|string|false|No description|
|»»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

<h1 id="EITI---API-documentation-Indicator-Values-v2">Indicator Values v2</h1>

## get__v2.0_indicator_value

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v2.0/indicator_value \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v2.0/indicator_value HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v2.0/indicator_value',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v2.0/indicator_value',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v2.0/indicator_value',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v2.0/indicator_value', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v2.0/indicator_value");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v2.0/indicator_value", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v2.0/indicator_value`

Fetches all the indicator values and their details as JSON objects

<h3 id="get__v2.0_indicator_value-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|filter[indicator]|query|integer|false|Allows to filter indicator values by their indicator|
|filter[source]|query|string|false|Allows to filter indicator values by their source|
|filter[summary_data]|query|string|false|Allows to filter indicator values by their summary data|

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "value": "string",
      "unit": "string",
      "indicator": "string",
      "source": "string",
      "summary_data": "string"
    }
  ],
  "count": 0,
  "self": {
    "title": "string",
    "href": "string"
  },
  "next": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v2.0_indicator_value-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v2.0_indicator_value-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» value|string|false|Depending of indicator type: numeric, text, boolean - yes, no, partially|
|»» unit|string|false|No description|
|»» indicator|string|false|No description|
|»» source|string|false|No description|
|»» summary_data|string|false|No description|
|» count|integer|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|
|» next|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

## get__v2.0_indicator_value_{id}

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v2.0/indicator_value/{id} \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v2.0/indicator_value/{id} HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v2.0/indicator_value/{id}',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v2.0/indicator_value/{id}',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v2.0/indicator_value/{id}',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v2.0/indicator_value/{id}', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v2.0/indicator_value/{id}");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v2.0/indicator_value/{id}", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v2.0/indicator_value/{id}`

Fetches a single indicator value and its details as a JSON object

<h3 id="get__v2.0_indicator_value_{id}-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|id|path|integer|false|No description|

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "value": "string",
      "unit": "string",
      "indicator": "string",
      "source": "string",
      "summary_data": "string"
    }
  ],
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v2.0_indicator_value_{id}-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v2.0_indicator_value_{id}-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» value|string|false|Depending of indicator type: numeric, text, boolean - yes, no, partially|
|»» unit|string|false|No description|
|»» indicator|string|false|No description|
|»» source|string|false|No description|
|»» summary_data|string|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

<h1 id="EITI---API-documentation-Organisation-v1">Organisation v1</h1>

## get__v1.0_organisation

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/organisation \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/organisation HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/organisation',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/organisation',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/organisation',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/organisation', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/organisation");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/organisation", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/organisation`

Fetches all the organisations and their information as JSON objects

<h3 id="get__v1.0_organisation-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|filter[type]|query|string|false|Allows to filter organisations by their type|
|filter[country]|query|string|false|Allows to filter organisations by their country id|
|filter[summary_data]|query|string|false|Allows to filter organisations by their summary data id (companies only)|
|filter[identification]|query|string|false|Allows to filter organisations by their identification|
|filter[sector]|query|string|false|Allows to filter organisations by their sector|
|filter[commodities]|query|string|false|Allows to filter organisations by a commodity|

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "type": "string",
      "country": 0,
      "summary_data": 0,
      "identification": "string",
      "sector": "string",
      "commodities": [
        "string"
      ]
    }
  ],
  "count": 0,
  "self": {
    "title": "string",
    "href": "string"
  },
  "next": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_organisation-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_organisation-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» type|string|false|No description|
|»» country|integer|false|No description|
|»» summary_data|integer|false|No description|
|»» identification|string|false|No description|
|»» sector|string|false|No description|
|»» commodities|[string]|false|No description|
|» count|integer|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|
|» next|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

## get__v1.0_organisation_{id}

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/organisation/{id} \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/organisation/{id} HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/organisation/{id}',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/organisation/{id}',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/organisation/{id}',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/organisation/{id}', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/organisation/{id}");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/organisation/{id}", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/organisation/{id}`

Fetches a single organisation and its information as a JSON object

<h3 id="get__v1.0_organisation_{id}-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|id|path|integer|false|No description|

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "type": "string",
      "country": 0,
      "summary_data": 0,
      "identification": "string",
      "sector": "string",
      "commodities": [
        "string"
      ]
    }
  ],
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_organisation_{id}-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_organisation_{id}-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» type|string|false|No description|
|»» country|integer|false|No description|
|»» summary_data|integer|false|No description|
|»» identification|string|false|No description|
|»» sector|string|false|No description|
|»» commodities|[string]|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

<h1 id="EITI---API-documentation-Organisation-v2">Organisation v2</h1>

## get__v2.0_organisation

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v2.0/organisation \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v2.0/organisation HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v2.0/organisation',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v2.0/organisation',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v2.0/organisation',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v2.0/organisation', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v2.0/organisation");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v2.0/organisation", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v2.0/organisation`

Fetches all the organisations and their information as JSON objects

<h3 id="get__v2.0_organisation-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|filter[type]|query|string|false|Allows to filter organisations by their type|
|filter[country]|query|string|false|Allows to filter organisations by their country id|
|filter[summary_data]|query|string|false|Allows to filter organisations by their summary data id|
|filter[identification]|query|string|false|Allows to filter organisations by their identification|
|filter[sector]|query|string|false|Allows to filter organisations by their sector|
|filter[commodities]|query|string|false|Allows to filter organisations by a commodity|

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "type": "string",
      "country": "string",
      "summary_data": [
        "string"
      ],
      "identification": "string",
      "sector": "string",
      "commodities": [
        "string"
      ]
    }
  ],
  "count": 0,
  "agencies": 0,
  "companies": 0,
  "companies_with_identification": 0,
  "companies_with_sector": 0,
  "companies_with_commodities": 0,
  "self": {
    "title": "string",
    "href": "string"
  },
  "next": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v2.0_organisation-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v2.0_organisation-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» type|string|false|No description|
|»» country|string|false|No description|
|»» summary_data|[string]|false|No description|
|»» identification|string|false|No description|
|»» sector|string|false|No description|
|»» commodities|[string]|false|No description|
|» count|integer|false|No description|
|» agencies|integer|false|Total number of agencies|
|» companies|integer|false|Total number of companies (note that unlike agencies companies are not shared between summary data entries)|
|» companies_with_identification|integer|false|No description|
|» companies_with_sector|integer|false|No description|
|» companies_with_commodities|integer|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|
|» next|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

## get__v2.0_organisation_{id}

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v2.0/organisation/{id} \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v2.0/organisation/{id} HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v2.0/organisation/{id}',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v2.0/organisation/{id}',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v2.0/organisation/{id}',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v2.0/organisation/{id}', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v2.0/organisation/{id}");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v2.0/organisation/{id}", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v2.0/organisation/{id}`

Fetches a single organisation and its information as a JSON object

<h3 id="get__v2.0_organisation_{id}-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|id|path|integer|false|No description|

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "type": "string",
      "country": "string",
      "summary_data": [
        "string"
      ],
      "identification": "string",
      "sector": "string",
      "commodities": [
        "string"
      ]
    }
  ],
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v2.0_organisation_{id}-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v2.0_organisation_{id}-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» type|string|false|No description|
|»» country|string|false|No description|
|»» summary_data|[string]|false|No description|
|»» identification|string|false|No description|
|»» sector|string|false|No description|
|»» commodities|[string]|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

<h1 id="EITI---API-documentation-Revenue-v1">Revenue v1</h1>

## get__v1.0_revenue

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/revenue \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/revenue HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/revenue',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/revenue',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/revenue',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/revenue', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/revenue");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/revenue", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/revenue`

Fetches all the revenue entries as JSON objects

<h3 id="get__v1.0_revenue-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|filter[type]|query|string|false|Allows to filter revenue entries by their type|
|filter[gfs]|query|string|false|Allows to filter revenue entries by their GFS code id|
|filter[report_status]|query|string|false|Allows to filter revenue entries by their report status|
|filter[organisation]|query|string|false|Allows to filter revenue entries by their organisation id|
|filter[revenue]|query|string|false|Allows to filter revenue entries by their revenue|
|filter[currency]|query|string|false|Allows to filter revenue entries by their currency|

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "type": "string",
      "gfs": {
        "id": 0,
        "label": "string",
        "self": "string",
        "code": "string",
        "parent": 0
      },
      "report_status": 0,
      "organisation": {
        "id": 0,
        "type": "string",
        "name": "string",
        "country_id": 0
      },
      "revenue": 0,
      "currency": "string"
    }
  ],
  "count": 0,
  "self": {
    "title": "string",
    "href": "string"
  },
  "next": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_revenue-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_revenue-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» type|string|false|No description|
|»» gfs|object|false|No description|
|»»» id|integer|false|No description|
|»»» label|string|false|No description|
|»»» self|string|false|No description|
|»»» code|string|false|No description|
|»»» parent|integer|false|No description|
|»» report_status|integer|false|No description|
|»» organisation|object|false|No description|
|»»» id|integer|false|No description|
|»»» type|string|false|No description|
|»»» name|string|false|No description|
|»»» country_id|integer|false|No description|
|»» revenue|number|false|No description|
|»» currency|string|false|No description|
|» count|integer|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|
|» next|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

## get__v1.0_revenue_{id}

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/revenue/{id} \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/revenue/{id} HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/revenue/{id}',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/revenue/{id}',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/revenue/{id}',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/revenue/{id}', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/revenue/{id}");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/revenue/{id}", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/revenue/{id}`

Fetches a single revenue entry as a JSON object

<h3 id="get__v1.0_revenue_{id}-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|id|path|integer|false|No description|

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "type": "string",
      "gfs": {
        "id": 0,
        "label": "string",
        "self": "string",
        "code": "string",
        "parent": 0
      },
      "report_status": 0,
      "organisation": {
        "id": 0,
        "type": "string",
        "name": "string",
        "country_id": 0,
        "status": true,
        "created": 0,
        "chnaged": 0
      },
      "revenue": 0,
      "currency": "string"
    }
  ],
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_revenue_{id}-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_revenue_{id}-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» type|string|false|No description|
|»» gfs|object|false|No description|
|»»» id|integer|false|No description|
|»»» label|string|false|No description|
|»»» self|string|false|No description|
|»»» code|string|false|No description|
|»»» parent|integer|false|No description|
|»» report_status|integer|false|No description|
|»» organisation|object|false|No description|
|»»» id|integer|false|No description|
|»»» type|string|false|No description|
|»»» name|string|false|No description|
|»»» country_id|integer|false|No description|
|»»» status|boolean|false|No description|
|»»» created|integer|false|No description|
|»»» chnaged|integer|false|No description|
|»» revenue|number|false|No description|
|»» currency|string|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

<h1 id="EITI---API-documentation-Revenue-v2">Revenue v2</h1>

## get__v2.0_revenue

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v2.0/revenue \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v2.0/revenue HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v2.0/revenue',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v2.0/revenue',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v2.0/revenue',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v2.0/revenue', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v2.0/revenue");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v2.0/revenue", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v2.0/revenue`

Fetches all the revenue entries as JSON objects

<h3 id="get__v2.0_revenue-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|filter[type]|query|string|false|Allows to filter revenue entries by their type|
|filter[gfs]|query|string|false|Allows to filter revenue entries by their GFS code id|
|filter[organisation]|query|string|false|Allows to filter revenue entries by their organisation id|
|filter[revenue]|query|string|false|Allows to filter revenue entries by their revenue|
|filter[currency]|query|string|false|Allows to filter revenue entries by their currency|
|filter[summary_data]|query|string|false|Allows to filter revenue entries by their summary data id|

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "type": "string",
      "gfs": "string",
      "organisation": "string",
      "revenue": 0,
      "currency": "string",
      "summary_data": "string"
    }
  ],
  "count": 0,
  "self": {
    "title": "string",
    "href": "string"
  },
  "next": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v2.0_revenue-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v2.0_revenue-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» type|string|false|No description|
|»» gfs|string|false|No description|
|»» organisation|string|false|No description|
|»» revenue|number|false|No description|
|»» currency|string|false|No description|
|»» summary_data|string|false|No description|
|» count|integer|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|
|» next|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

## get__v2.0_revenue_{id}

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v2.0/revenue/{id} \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v2.0/revenue/{id} HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v2.0/revenue/{id}',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v2.0/revenue/{id}',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v2.0/revenue/{id}',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v2.0/revenue/{id}', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v2.0/revenue/{id}");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v2.0/revenue/{id}", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v2.0/revenue/{id}`

Fetches a single revenue entry as a JSON object

<h3 id="get__v2.0_revenue_{id}-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|id|path|integer|false|No description|

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "type": "string",
      "gfs": "string",
      "organisation": "string",
      "revenue": 0,
      "currency": "string",
      "summary_data": "string"
    }
  ],
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v2.0_revenue_{id}-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v2.0_revenue_{id}-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» type|string|false|No description|
|»» gfs|string|false|No description|
|»» organisation|string|false|No description|
|»» revenue|number|false|No description|
|»» currency|string|false|No description|
|»» summary_data|string|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

<h1 id="EITI---API-documentation-Score-Data-v1">Score Data v1</h1>

## get__v1.0_score_data

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/score_data \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/score_data HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/score_data',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/score_data',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/score_data',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/score_data', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/score_data");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/score_data", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/score_data`

Data about the progress of countries in meeting the requirements of the EITI Standard. All implementing countries are held to the same global standard. Every country that joins the EITI as a member is assessed against the EITI Standard in a process called Validation. EITI Validation reviews the country’s progress against the EITI Requirements, analyses the impact, and makes recommendations for strengthening the process and improving the governance of the sector. Depending on the outcome of its Validation, the country is re-assessed anywhere between three months and three years. This encourages continuous improvement and safeguards the integrity of the EITI. The EITI Board, through the EITI Secretariat, oversees the Validation process. The Board then ascribes the country as having made satisfactory progress (sometimes referred to as ‘compliance’), meaningful progress, inadequate progress or no progress.

<h3 id="get__v1.0_score_data-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|filter[year]|query|string|false|Allows to filter score data by their year|
|filter[country]|query|string|false|Allows to filter score data by their country id|
|filter[score_req_values]|query|string|false|Allows to filter score data by their score requirement values id|

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "year": 0,
      "country": {
        "id": 0,
        "label": "string",
        "self": "string",
        "iso2": "string",
        "iso3": "string",
        "status": {
          "tid": 0,
          "language": "string",
          "name": "string",
          "color": "string"
        },
        "status_date": 0,
        "local_website": "string",
        "annual_report_file": "string",
        "reports": {
          "property1": [
            {
              "commodity": "string",
              "parent": "string",
              "id": 0,
              "value": 0,
              "value_bool": 0,
              "value_text": "string",
              "unit": "string",
              "source": "string"
            }
          ],
          "property2": [
            {
              "commodity": "string",
              "parent": "string",
              "id": 0,
              "value": 0,
              "value_bool": 0,
              "value_text": "string",
              "unit": "string",
              "source": "string"
            }
          ]
        },
        "metadata": {
          "property1": {
            "contact": {
              "name": "string",
              "email": "string",
              "organisation": "string"
            },
            "year_start": "string",
            "year_end": "string",
            "currency_rate": 0,
            "currency_code": "string",
            "sectors_covered": [
              "string"
            ],
            "reporting_organisations": {
              "companies": 0,
              "governmental_agencies": 0
            },
            "web_report_links": [
              {
                "url": "string",
                "title": "string",
                "attributes": []
              }
            ],
            "disaggregated": {
              "project": 0,
              "revenue_stream": 0,
              "company": 0
            }
          },
          "property2": {
            "contact": {
              "name": "string",
              "email": "string",
              "organisation": "string"
            },
            "year_start": "string",
            "year_end": "string",
            "currency_rate": 0,
            "currency_code": "string",
            "sectors_covered": [
              "string"
            ],
            "reporting_organisations": {
              "companies": 0,
              "governmental_agencies": 0
            },
            "web_report_links": [
              {
                "url": "string",
                "title": "string",
                "attributes": []
              }
            ],
            "disaggregated": {
              "project": 0,
              "revenue_stream": 0,
              "company": 0
            }
          }
        },
        "licenses": {
          "property1": {
            "property1": "string",
            "property2": "string"
          },
          "property2": {
            "property1": "string",
            "property2": "string"
          }
        },
        "contracts": {
          "property1": {
            "property1": "string",
            "property2": "string"
          },
          "property2": {
            "property1": "string",
            "property2": "string"
          }
        },
        "revenues": {
          "property1": {
            "government": 0,
            "company": 0
          },
          "property2": {
            "government": 0,
            "company": 0
          }
        }
      },
      "score_req_values": [
        {
          "id": 0,
          "score_req_id": 0,
          "score_req": {
            "id": 0,
            "type": "string",
            "status": 0,
            "created": 0,
            "name": "string",
            "code": "string",
            "field_score_req_category": {
              "und": [
                {
                  "tid": 0
                }
              ]
            }
          },
          "value": 0,
          "progress_value": 0,
          "is_applicable": 0,
          "is_required": 0,
          "description": "string"
        }
      ]
    }
  ],
  "count": 0,
  "self": {
    "title": "string",
    "href": "string"
  },
  "next": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_score_data-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_score_data-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|The score_data identifier|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» year|integer|false|No description|
|»» country|object|false|No description|
|»»» id|integer|false|No description|
|»»» label|string|false|No description|
|»»» self|string|false|No description|
|»»» iso2|string|false|No description|
|»»» iso3|string|false|No description|
|»»» status|object|false|No description|
|»»»» tid|integer|false|No description|
|»»»» language|string|false|No description|
|»»»» name|string|false|No description|
|»»»» color|string|false|No description|
|»»» status_date|integer|false|No description|
|»»» local_website|string|false|No description|
|»»» annual_report_file|string|false|No description|
|»»» reports|object|false|No description|
|»»»» **additionalProperties**|[object]|false|No description|
|»»»»» commodity|string|false|No description|
|»»»»» parent|string|false|No description|
|»»»»» id|integer|false|No description|
|»»»»» value|integer|false|No description|
|»»»»» value_bool|integer|false|No description|
|»»»»» value_text|string|false|No description|
|»»»»» unit|string|false|No description|
|»»»»» source|string|false|No description|
|»»»» metadata|object|false|No description|
|»»»»» **additionalProperties**|object|false|No description|
|»»»»»» contact|object|false|No description|
|»»»»»»» name|string|false|No description|
|»»»»»»» email|string|false|No description|
|»»»»»»» organisation|string|false|No description|
|»»»»»» year_start|string|false|No description|
|»»»»»» year_end|string|false|No description|
|»»»»»» currency_rate|number|false|No description|
|»»»»»» currency_code|string|false|No description|
|»»»»»» sectors_covered|[string]|false|No description|
|»»»»»» reporting_organisations|object|false|No description|
|»»»»»»» companies|integer|false|No description|
|»»»»»»» governmental_agencies|integer|false|No description|
|»»»»»» web_report_links|[object]|false|No description|
|»»»»»»» url|string|false|No description|
|»»»»»»» title|string|false|No description|
|»»»»»»» attributes|array|false|No description|
|»»»»»» disaggregated|object|false|No description|
|»»»»»»» project|integer|false|No description|
|»»»»»»» revenue_stream|integer|false|No description|
|»»»»»»» company|integer|false|No description|
|»»»»»» licenses|object|false|No description|
|»»»»»»» **additionalProperties**|object|false|No description|
|»»»»»»»» **additionalProperties**|string|false|No description|
|»»»»»»» contracts|object|false|No description|
|»»»»»»»» **additionalProperties**|object|false|No description|
|»»»»»»»»» **additionalProperties**|string|false|No description|
|»»»»»»»» revenues|object|false|No description|
|»»»»»»»»» **additionalProperties**|object|false|No description|
|»»»»»»»»»» government|integer|false|No description|
|»»»»»»»»»» company|integer|false|No description|
|»»»»»»»»» score_req_values|[object]|false|No description|
|»»»»»»»»»» id|integer|false|No description|
|»»»»»»»»»» score_req_id|integer|false|No description|
|»»»»»»»»»» score_req|object|false|No description|
|»»»»»»»»»»» id|integer|false|No description|
|»»»»»»»»»»» type|string|false|No description|
|»»»»»»»»»»» status|integer|false|No description|
|»»»»»»»»»»» created|integer|false|No description|
|»»»»»»»»»»» name|string|false|No description|
|»»»»»»»»»»» code|string|false|No description|
|»»»»»»»»»»» field_score_req_category|object|false|No description|
|»»»»»»»»»»»» und|[object]|false|No description|
|»»»»»»»»»»»»» tid|integer|false|No description|
|»»»»»»»»»»»» value|integer|false|No description|
|»»»»»»»»»»»» progress_value|integer|false|No description|
|»»»»»»»»»»»» is_applicable|integer|false|No description|
|»»»»»»»»»»»» is_required|integer|false|No description|
|»»»»»»»»»»»» description|string|false|No description|
|»»»»»»»»»»» count|integer|false|No description|
|»»»»»»»»»»» self|object|false|No description|
|»»»»»»»»»»»» title|string|false|No description|
|»»»»»»»»»»»» href|string|false|No description|
|»»»»»»»»»»» next|object|false|No description|
|»»»»»»»»»»»» title|string|false|No description|
|»»»»»»»»»»»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

## get__v1.0_score_data_{id}

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/score_data/{id} \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/score_data/{id} HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/score_data/{id}',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/score_data/{id}',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/score_data/{id}',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/score_data/{id}', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/score_data/{id}");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/score_data/{id}", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/score_data/{id}`

Data about the progress of a country in a specific year in meeting the requirements of the EITI Standard. All implementing countries are held to the same global standard. Every country that joins the EITI as a member is assessed against the EITI Standard in a process called Validation. EITI Validation reviews the country’s progress against the EITI Requirements, analyses the impact, and makes recommendations for strengthening the process and improving the governance of the sector. Depending on the outcome of its Validation, the country is re-assessed anywhere between three months and three years. This encourages continuous improvement and safeguards the integrity of the EITI. The EITI Board, through the EITI Secretariat, oversees the Validation process. The Board then ascribes the country as having made satisfactory progress (sometimes referred to as ‘compliance’), meaningful progress, inadequate progress or no progress.

<h3 id="get__v1.0_score_data_{id}-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|id|path|integer|false|No description|

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "year": 0,
      "country": {
        "id": 0,
        "label": "string",
        "self": "string",
        "iso2": "string",
        "iso3": "string",
        "status": {
          "tid": 0,
          "language": "string",
          "name": "string",
          "color": "string"
        },
        "status_date": 0,
        "local_website": "string",
        "annual_report_file": "string",
        "reports": {
          "property1": [
            {
              "commodity": "string",
              "parent": "string",
              "id": 0,
              "value": 0,
              "value_bool": 0,
              "value_text": "string",
              "unit": "string",
              "source": "string"
            }
          ],
          "property2": [
            {
              "commodity": "string",
              "parent": "string",
              "id": 0,
              "value": 0,
              "value_bool": 0,
              "value_text": "string",
              "unit": "string",
              "source": "string"
            }
          ]
        },
        "metadata": {
          "property1": {
            "contact": {
              "name": "string",
              "email": "string",
              "organisation": "string"
            },
            "year_start": "string",
            "year_end": "string",
            "currency_rate": 0,
            "currency_code": "string",
            "sectors_covered": [
              "string"
            ],
            "reporting_organisations": {
              "companies": 0,
              "governmental_agencies": 0
            },
            "web_report_links": [
              {
                "url": "string",
                "title": "string",
                "attributes": []
              }
            ],
            "disaggregated": {
              "project": 0,
              "revenue_stream": 0,
              "company": 0
            }
          },
          "property2": {
            "contact": {
              "name": "string",
              "email": "string",
              "organisation": "string"
            },
            "year_start": "string",
            "year_end": "string",
            "currency_rate": 0,
            "currency_code": "string",
            "sectors_covered": [
              "string"
            ],
            "reporting_organisations": {
              "companies": 0,
              "governmental_agencies": 0
            },
            "web_report_links": [
              {
                "url": "string",
                "title": "string",
                "attributes": []
              }
            ],
            "disaggregated": {
              "project": 0,
              "revenue_stream": 0,
              "company": 0
            }
          }
        },
        "licenses": {
          "property1": {
            "property1": "string",
            "property2": "string"
          },
          "property2": {
            "property1": "string",
            "property2": "string"
          }
        },
        "contracts": {
          "property1": {
            "property1": "string",
            "property2": "string"
          },
          "property2": {
            "property1": "string",
            "property2": "string"
          }
        },
        "revenues": {
          "property1": {
            "government": 0,
            "company": 0
          },
          "property2": {
            "government": 0,
            "company": 0
          }
        }
      },
      "score_req_values": [
        {
          "id": 0,
          "score_req_id": 0,
          "score_req": {
            "id": 0,
            "type": "string",
            "status": 0,
            "created": 0,
            "name": "string",
            "code": "string",
            "field_score_req_category": {
              "und": [
                {
                  "tid": 0
                }
              ]
            }
          },
          "value": 0,
          "progress_value": 0,
          "is_applicable": 0,
          "is_required": 0,
          "description": "string"
        }
      ]
    }
  ],
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_score_data_{id}-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_score_data_{id}-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|The score_data identifier|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» year|integer|false|No description|
|»» country|object|false|No description|
|»»» id|integer|false|No description|
|»»» label|string|false|No description|
|»»» self|string|false|No description|
|»»» iso2|string|false|No description|
|»»» iso3|string|false|No description|
|»»» status|object|false|No description|
|»»»» tid|integer|false|No description|
|»»»» language|string|false|No description|
|»»»» name|string|false|No description|
|»»»» color|string|false|No description|
|»»» status_date|integer|false|No description|
|»»» local_website|string|false|No description|
|»»» annual_report_file|string|false|No description|
|»»» reports|object|false|No description|
|»»»» **additionalProperties**|[object]|false|No description|
|»»»»» commodity|string|false|No description|
|»»»»» parent|string|false|No description|
|»»»»» id|integer|false|No description|
|»»»»» value|integer|false|No description|
|»»»»» value_bool|integer|false|No description|
|»»»»» value_text|string|false|No description|
|»»»»» unit|string|false|No description|
|»»»»» source|string|false|No description|
|»»»» metadata|object|false|No description|
|»»»»» **additionalProperties**|object|false|No description|
|»»»»»» contact|object|false|No description|
|»»»»»»» name|string|false|No description|
|»»»»»»» email|string|false|No description|
|»»»»»»» organisation|string|false|No description|
|»»»»»» year_start|string|false|No description|
|»»»»»» year_end|string|false|No description|
|»»»»»» currency_rate|number|false|No description|
|»»»»»» currency_code|string|false|No description|
|»»»»»» sectors_covered|[string]|false|No description|
|»»»»»» reporting_organisations|object|false|No description|
|»»»»»»» companies|integer|false|No description|
|»»»»»»» governmental_agencies|integer|false|No description|
|»»»»»» web_report_links|[object]|false|No description|
|»»»»»»» url|string|false|No description|
|»»»»»»» title|string|false|No description|
|»»»»»»» attributes|array|false|No description|
|»»»»»» disaggregated|object|false|No description|
|»»»»»»» project|integer|false|No description|
|»»»»»»» revenue_stream|integer|false|No description|
|»»»»»»» company|integer|false|No description|
|»»»»»» licenses|object|false|No description|
|»»»»»»» **additionalProperties**|object|false|No description|
|»»»»»»»» **additionalProperties**|string|false|No description|
|»»»»»»» contracts|object|false|No description|
|»»»»»»»» **additionalProperties**|object|false|No description|
|»»»»»»»»» **additionalProperties**|string|false|No description|
|»»»»»»»» revenues|object|false|No description|
|»»»»»»»»» **additionalProperties**|object|false|No description|
|»»»»»»»»»» government|integer|false|No description|
|»»»»»»»»»» company|integer|false|No description|
|»»»»»»»»» score_req_values|[object]|false|No description|
|»»»»»»»»»» id|integer|false|No description|
|»»»»»»»»»» score_req_id|integer|false|No description|
|»»»»»»»»»» score_req|object|false|No description|
|»»»»»»»»»»» id|integer|false|No description|
|»»»»»»»»»»» type|string|false|No description|
|»»»»»»»»»»» status|integer|false|No description|
|»»»»»»»»»»» created|integer|false|No description|
|»»»»»»»»»»» name|string|false|No description|
|»»»»»»»»»»» code|string|false|No description|
|»»»»»»»»»»» field_score_req_category|object|false|No description|
|»»»»»»»»»»»» und|[object]|false|No description|
|»»»»»»»»»»»»» tid|integer|false|No description|
|»»»»»»»»»»»» value|integer|false|No description|
|»»»»»»»»»»»» progress_value|integer|false|No description|
|»»»»»»»»»»»» is_applicable|integer|false|No description|
|»»»»»»»»»»»» is_required|integer|false|No description|
|»»»»»»»»»»»» description|string|false|No description|
|»»»»»»»»»»» self|object|false|No description|
|»»»»»»»»»»»» title|string|false|No description|
|»»»»»»»»»»»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

<h1 id="EITI---API-documentation-Validation-Data-v2">Validation Data v2</h1>

## get__v2.0_validation_data

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v2.0/validation_data \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v2.0/validation_data HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v2.0/validation_data',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v2.0/validation_data',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v2.0/validation_data',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v2.0/validation_data', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v2.0/validation_data");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v2.0/validation_data", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v2.0/validation_data`

Data about the progress of countries in meeting the requirements of the EITI Standard. All implementing countries are held to the same global standard. Every country that joins the EITI as a member is assessed against the EITI Standard in a process called Validation. EITI Validation reviews the country’s progress against the EITI Requirements, analyses the impact, and makes recommendations for strengthening the process and improving the governance of the sector. Depending on the outcome of its Validation, the country is re-assessed anywhere between three months and three years. This encourages continuous improvement and safeguards the integrity of the EITI. The EITI Board, through the EITI Secretariat, oversees the Validation process. The Board then ascribes the country as having made satisfactory progress (sometimes referred to as ‘compliance’), meaningful progress, inadequate progress or no progress.

<h3 id="get__v2.0_validation_data-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|filter[year]|query|string|false|Allows to filter score data by their year|
|filter[country]|query|string|false|Allows to filter score data by their country id|
|filter[score_req_values]|query|string|false|Allows to filter score data by their score requirement values id|

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "year": 0,
      "board_decision_url": "string",
      "validation_documentation": "string",
      "country": "string",
      "validation_date": "string",
      "overall_progress": {
        "id": 0,
        "score_req": {
          "id": 0,
          "name": "string",
          "requirement": "string",
          "category": "string"
        },
        "progress_value": 0,
        "is_applicable": true,
        "is_required": true,
        "description": "string"
      },
      "score_req_values": [
        {
          "id": 0,
          "score_req": {
            "id": 0,
            "name": "string",
            "requirement": "string",
            "category": "string"
          },
          "progress_value": 0,
          "is_applicable": true,
          "is_required": true,
          "description": "string"
        }
      ]
    }
  ],
  "count": 0,
  "validation_data_description": "string",
  "self": {
    "title": "string",
    "href": "string"
  },
  "next": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v2.0_validation_data-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v2.0_validation_data-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» year|integer|false|No description|
|»» board_decision_url|string|false|No description|
|»» validation_documentation|string|false|No description|
|»» country|string|false|No description|
|»» validation_date|string|false|No description|
|»» overall_progress|object|false|No description|
|»»» id|integer|false|No description|
|»»» score_req|object|false|No description|
|»»»» id|integer|false|No description|
|»»»» name|string|false|No description|
|»»»» requirement|string|false|No description|
|»»»» category|string|false|No description|
|»»» progress_value|integer|false|No description|
|»»» is_applicable|boolean|false|No description|
|»»» is_required|boolean|false|No description|
|»»» description|string|false|No description|
|»» score_req_values|[object]|false|No description|
|»»» id|integer|false|No description|
|»»» score_req|object|false|No description|
|»»»» id|integer|false|No description|
|»»»» name|string|false|No description|
|»»»» requirement|string|false|No description|
|»»»» category|string|false|No description|
|»»» progress_value|integer|false|No description|
|»»» is_applicable|boolean|false|No description|
|»»» is_required|boolean|false|No description|
|»»» description|string|false|No description|
|»» count|integer|false|No description|
|»» validation_data_description|string|false|No description|
|»» self|object|false|No description|
|»»» title|string|false|No description|
|»»» href|string|false|No description|
|»» next|object|false|No description|
|»»» title|string|false|No description|
|»»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

## get__v2.0_validation_data_{id}

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v2.0/validation_data/{id} \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v2.0/validation_data/{id} HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v2.0/validation_data/{id}',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v2.0/validation_data/{id}',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v2.0/validation_data/{id}',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v2.0/validation_data/{id}', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v2.0/validation_data/{id}");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v2.0/validation_data/{id}", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v2.0/validation_data/{id}`

Data about the progress of a country in a specific year in meeting the requirements of the EITI Standard. All implementing countries are held to the same global standard. Every country that joins the EITI as a member is assessed against the EITI Standard in a process called Validation. EITI Validation reviews the country’s progress against the EITI Requirements, analyses the impact, and makes recommendations for strengthening the process and improving the governance of the sector. Depending on the outcome of its Validation, the country is re-assessed anywhere between three months and three years. This encourages continuous improvement and safeguards the integrity of the EITI. The EITI Board, through the EITI Secretariat, oversees the Validation process. The Board then ascribes the country as having made satisfactory progress (sometimes referred to as ‘compliance’), meaningful progress, inadequate progress or no progress.

<h3 id="get__v2.0_validation_data_{id}-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|id|path|integer|false|No description|

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "year": 0,
      "board_decision_url": "string",
      "validation_documentation": "string",
      "country": "string",
      "validation_date": "string",
      "overall_progress": {
        "id": 0,
        "score_req": {
          "id": 0,
          "name": "string",
          "requirement": "string",
          "category": "string"
        },
        "progress_value": 0,
        "is_applicable": true,
        "is_required": true,
        "description": "string"
      },
      "score_req_values": [
        {
          "id": 0,
          "score_req": {
            "id": 0,
            "name": "string",
            "requirement": "string",
            "category": "string"
          },
          "progress_value": 0,
          "is_applicable": true,
          "is_required": true,
          "description": "string"
        }
      ]
    }
  ],
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v2.0_validation_data_{id}-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v2.0_validation_data_{id}-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» year|integer|false|No description|
|»» board_decision_url|string|false|No description|
|»» validation_documentation|string|false|No description|
|»» country|string|false|No description|
|»» validation_date|string|false|No description|
|»» overall_progress|object|false|No description|
|»»» id|integer|false|No description|
|»»» score_req|object|false|No description|
|»»»» id|integer|false|No description|
|»»»» name|string|false|No description|
|»»»» requirement|string|false|No description|
|»»»» category|string|false|No description|
|»»» progress_value|integer|false|No description|
|»»» is_applicable|boolean|false|No description|
|»»» is_required|boolean|false|No description|
|»»» description|string|false|No description|
|»» score_req_values|[object]|false|No description|
|»»» id|integer|false|No description|
|»»» score_req|object|false|No description|
|»»»» id|integer|false|No description|
|»»»» name|string|false|No description|
|»»»» requirement|string|false|No description|
|»»»» category|string|false|No description|
|»»» progress_value|integer|false|No description|
|»»» is_applicable|boolean|false|No description|
|»»» is_required|boolean|false|No description|
|»»» description|string|false|No description|
|»» self|object|false|No description|
|»»» title|string|false|No description|
|»»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

<h1 id="EITI---API-documentation-Summary-Data-v1">Summary Data v1</h1>

## get__v1.0_summary_data

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/summary_data \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/summary_data HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/summary_data',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/summary_data',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/summary_data',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/summary_data', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/summary_data");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/summary_data", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/summary_data`

Summary data is EITI’s tool for collecting and publishing data from EITI Reports in structured way. The summary data files are excel files, which are filled out by our implementing countries using the Summary Data Template. The national secretariats submit one excel-file for every fiscal year covered by an EITI Report.

<h3 id="get__v1.0_summary_data-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|filter[links]|query|string|false|Allows to filter summary data by their links URL|
|filter[email]|query|string|false|Allows to filter summary data by their email|
|filter[government_entities_nr]|query|string|false|Allows to filter summary data by their government entities number|
|filter[company_entities_nr]|query|string|false|Allows to filter summary data by their company entities number|
|filter[year_start]|query|string|false|Allows to filter summary data by their start year (GMT UNIX timestamp of January 1)|
|filter[year_end]|query|string|false|Allows to filter summary data by their end year (GMT UNIX timestamp of December 31)|
|filter[created]|query|string|false|Allows to filter summary data by their created date UNIX timestamp (mismatch with display)|
|filter[changed]|query|string|false|Allows to filter summary data by their changed date UNIX timestamp (mismatch with display)|
|filter[sector_oil]|query|string|false|Allows to filter summary data by their oil sector|
|filter[sector_mining]|query|string|false|Allows to filter summary data by their mining sector|
|filter[sector_gas]|query|string|false|Allows to filter summary data by their gas sector|
|filter[sector_other]|query|string|false|Allows to filter summary data by their other sectors|
|filter[report_file]|query|string|false|Allows to filter summary data by their report file id|
|filter[country]|query|string|false|Allows to filter summary data by their country id|
|filter[indicator_values]|query|string|false|Allows to filter summary data by their indicator values id|
|filter[revenue_government]|query|string|false|Allows to filter summary data by their government revenue id|
|filter[revenue_company]|query|string|false|Allows to filter summary data by their company revenue id|

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "links": [
        "string"
      ],
      "email": "string",
      "government_entities_nr": 0,
      "company_entities_nr": 0,
      "year_start": "string",
      "year_end": "string",
      "created": "string",
      "changed": "string",
      "sector_oil": 0,
      "sector_mining": 0,
      "sector_gas": 0,
      "sector_other": "string",
      "report_file": "string",
      "country": {
        "id": 0,
        "label": "string",
        "self": "string",
        "iso2": "string",
        "iso3": "string",
        "status": {
          "tid": 0,
          "language": "string",
          "name": "string",
          "color": "string"
        },
        "status_date": 0,
        "local_website": "string",
        "annual_report_file": "string",
        "reports": {
          "property1": [
            {
              "commodity": "string",
              "parent": "string",
              "id": 0,
              "value": 0,
              "value_bool": 0,
              "value_text": "string",
              "unit": "string",
              "source": "string"
            }
          ],
          "property2": [
            {
              "commodity": "string",
              "parent": "string",
              "id": 0,
              "value": 0,
              "value_bool": 0,
              "value_text": "string",
              "unit": "string",
              "source": "string"
            }
          ]
        },
        "metadata": {
          "property1": {
            "contact": {
              "name": "string",
              "email": "string",
              "organisation": "string"
            },
            "year_start": "string",
            "year_end": "string",
            "currency_rate": 0,
            "currency_code": "string",
            "sectors_covered": [
              "string"
            ],
            "reporting_organisations": {
              "companies": 0,
              "governmental_agencies": 0
            },
            "web_report_links": [
              {
                "url": "string",
                "title": "string",
                "attributes": []
              }
            ],
            "disaggregated": {
              "project": 0,
              "revenue_stream": 0,
              "company": 0
            }
          },
          "property2": {
            "contact": {
              "name": "string",
              "email": "string",
              "organisation": "string"
            },
            "year_start": "string",
            "year_end": "string",
            "currency_rate": 0,
            "currency_code": "string",
            "sectors_covered": [
              "string"
            ],
            "reporting_organisations": {
              "companies": 0,
              "governmental_agencies": 0
            },
            "web_report_links": [
              {
                "url": "string",
                "title": "string",
                "attributes": []
              }
            ],
            "disaggregated": {
              "project": 0,
              "revenue_stream": 0,
              "company": 0
            }
          }
        },
        "licenses": {
          "property1": {
            "property1": "string",
            "property2": "string"
          },
          "property2": {
            "property1": "string",
            "property2": "string"
          }
        },
        "contracts": {
          "property1": {
            "property1": "string",
            "property2": "string"
          },
          "property2": {
            "property1": "string",
            "property2": "string"
          }
        },
        "revenues": {
          "property1": {
            "government": 0,
            "company": 0
          },
          "property2": {
            "government": 0,
            "company": 0
          }
        },
        "latest_validation_date": "string",
        "latest_validation_link": "string",
        "latest_validation_url": "string"
      },
      "indicator_values": [
        {
          "id": 0,
          "label": "string",
          "self": "string",
          "value": 0,
          "unit": "string",
          "indicator": {
            "id": 0,
            "type": "string",
            "name": "string",
            "parent": 0,
            "status": 0,
            "created": 0
          }
        }
      ],
      "revenue_government": [
        {
          "id": 0,
          "type": "string",
          "gfs_code_id": 0,
          "report_status": 0,
          "name": "string",
          "organisation_id": 0,
          "revenue": 0,
          "currency": "string",
          "original_revenue": 0,
          "original_currency": "string"
        }
      ],
      "revenue_company": [
        {
          "id": 0,
          "type": "string",
          "gfs_code_id": 0,
          "report_status": 0,
          "name": "string",
          "organisation_id": 0,
          "revenue": 0,
          "currency": "string",
          "original_revenue": 0,
          "original_currency": "string"
        }
      ]
    }
  ],
  "count": 0,
  "self": {
    "title": "string",
    "href": "string"
  },
  "next": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_summary_data-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_summary_data-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» links|[string]|false|No description|
|»» email|string|false|No description|
|»» government_entities_nr|number|false|No description|
|»» company_entities_nr|number|false|No description|
|»» year_start|string|false|No description|
|»» year_end|string|false|No description|
|»» created|string|false|No description|
|»» changed|string|false|No description|
|»» sector_oil|integer|false|No description|
|»» sector_mining|integer|false|No description|
|»» sector_gas|integer|false|No description|
|»» sector_other|string|false|No description|
|»» report_file|string|false|No description|
|»» country|object|false|No description|
|»»» id|integer|false|No description|
|»»» label|string|false|No description|
|»»» self|string|false|No description|
|»»» iso2|string|false|No description|
|»»» iso3|string|false|No description|
|»»» status|object|false|No description|
|»»»» tid|integer|false|No description|
|»»»» language|string|false|No description|
|»»»» name|string|false|No description|
|»»»» color|string|false|No description|
|»»» status_date|integer|false|No description|
|»»» local_website|string|false|No description|
|»»» annual_report_file|string|false|No description|
|»»» reports|object|false|No description|
|»»»» **additionalProperties**|[object]|false|No description|
|»»»»» commodity|string|false|No description|
|»»»»» parent|string|false|No description|
|»»»»» id|integer|false|No description|
|»»»»» value|integer|false|No description|
|»»»»» value_bool|integer|false|No description|
|»»»»» value_text|string|false|No description|
|»»»»» unit|string|false|No description|
|»»»»» source|string|false|No description|
|»»»» metadata|object|false|No description|
|»»»»» **additionalProperties**|object|false|No description|
|»»»»»» contact|object|false|No description|
|»»»»»»» name|string|false|No description|
|»»»»»»» email|string|false|No description|
|»»»»»»» organisation|string|false|No description|
|»»»»»» year_start|string|false|No description|
|»»»»»» year_end|string|false|No description|
|»»»»»» currency_rate|number|false|No description|
|»»»»»» currency_code|string|false|No description|
|»»»»»» sectors_covered|[string]|false|No description|
|»»»»»» reporting_organisations|object|false|No description|
|»»»»»»» companies|integer|false|No description|
|»»»»»»» governmental_agencies|integer|false|No description|
|»»»»»» web_report_links|[object]|false|No description|
|»»»»»»» url|string|false|No description|
|»»»»»»» title|string|false|No description|
|»»»»»»» attributes|array|false|No description|
|»»»»»» disaggregated|object|false|No description|
|»»»»»»» project|integer|false|No description|
|»»»»»»» revenue_stream|integer|false|No description|
|»»»»»»» company|integer|false|No description|
|»»»»»» licenses|object|false|No description|
|»»»»»»» **additionalProperties**|object|false|No description|
|»»»»»»»» **additionalProperties**|string|false|No description|
|»»»»»»» contracts|object|false|No description|
|»»»»»»»» **additionalProperties**|object|false|No description|
|»»»»»»»»» **additionalProperties**|string|false|No description|
|»»»»»»»» revenues|object|false|No description|
|»»»»»»»»» **additionalProperties**|object|false|No description|
|»»»»»»»»»» government|integer|false|No description|
|»»»»»»»»»» company|integer|false|No description|
|»»»»»»»»» latest_validation_date|string|false|No description|
|»»»»»»»»» latest_validation_link|string|false|No description|
|»»»»»»»»» latest_validation_url|string|false|No description|
|»»»»»»»» indicator_values|[object]|false|No description|
|»»»»»»»»» id|integer|false|No description|
|»»»»»»»»» label|string|false|No description|
|»»»»»»»»» self|string|false|No description|
|»»»»»»»»» value|integer|false|No description|
|»»»»»»»»» unit|string|false|No description|
|»»»»»»»»» indicator|object|false|No description|
|»»»»»»»»»» id|integer|false|No description|
|»»»»»»»»»» type|string|false|No description|
|»»»»»»»»»» name|string|false|No description|
|»»»»»»»»»» parent|integer|false|No description|
|»»»»»»»»»» status|integer|false|No description|
|»»»»»»»»»» created|integer|false|No description|
|»»»»»»»»» revenue_government|[object]|false|No description|
|»»»»»»»»»» id|integer|false|No description|
|»»»»»»»»»» type|string|false|No description|
|»»»»»»»»»» gfs_code_id|integer|false|No description|
|»»»»»»»»»» report_status|integer|false|No description|
|»»»»»»»»»» name|string|false|No description|
|»»»»»»»»»» organisation_id|integer|false|No description|
|»»»»»»»»»» revenue|number|false|No description|
|»»»»»»»»»» currency|string|false|No description|
|»»»»»»»»»» original_revenue|number|false|No description|
|»»»»»»»»»» original_currency|string|false|No description|
|»»»»»»»»» revenue_company|[object]|false|No description|
|»»»»»»»»»» id|integer|false|No description|
|»»»»»»»»»» type|string|false|No description|
|»»»»»»»»»» gfs_code_id|integer|false|No description|
|»»»»»»»»»» report_status|integer|false|No description|
|»»»»»»»»»» name|string|false|No description|
|»»»»»»»»»» organisation_id|integer|false|No description|
|»»»»»»»»»» revenue|number|false|No description|
|»»»»»»»»»» currency|string|false|No description|
|»»»»»»»»»» original_revenue|number|false|No description|
|»»»»»»»»»» original_currency|string|false|No description|
|»»»»»»»»» count|integer|false|No description|
|»»»»»»»»» self|object|false|No description|
|»»»»»»»»»» title|string|false|No description|
|»»»»»»»»»» href|string|false|No description|
|»»»»»»»»» next|object|false|No description|
|»»»»»»»»»» title|string|false|No description|
|»»»»»»»»»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

## get__v1.0_summary_data_{id}

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/summary_data/{id} \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/summary_data/{id} HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/summary_data/{id}',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/summary_data/{id}',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/summary_data/{id}',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/summary_data/{id}', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/summary_data/{id}");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/summary_data/{id}", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/summary_data/{id}`

Fetches a single summary data entry. Summary data is EITI’s tool for collecting and publishing data from EITI Reports in structured way. The summary data files are excel files, which are filled out by our implementing countries using the Summary Data Template. The national secretariats submit one excel-file for every fiscal year covered by an EITI Report.

<h3 id="get__v1.0_summary_data_{id}-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|id|path|integer|false|No description|

> Example responses

```json
{
  "data": [
    {
      "id": 0,
      "label": "string",
      "self": "string",
      "links": [
        "string"
      ],
      "email": "string",
      "government_entities_nr": 0,
      "company_entities_nr": 0,
      "year_start": "string",
      "year_end": "string",
      "created": "string",
      "changed": "string",
      "sector_oil": 0,
      "sector_mining": 0,
      "sector_gas": 0,
      "sector_other": "string",
      "report_file": "string",
      "country": {
        "id": 0,
        "label": "string",
        "self": "string",
        "iso2": "string",
        "iso3": "string",
        "status": {
          "tid": 0,
          "language": "string",
          "name": "string",
          "color": "string"
        },
        "status_date": 0,
        "local_website": "string",
        "annual_report_file": "string",
        "reports": {
          "property1": [
            {
              "commodity": "string",
              "parent": "string",
              "id": 0,
              "value": 0,
              "value_bool": 0,
              "value_text": "string",
              "unit": "string",
              "source": "string"
            }
          ],
          "property2": [
            {
              "commodity": "string",
              "parent": "string",
              "id": 0,
              "value": 0,
              "value_bool": 0,
              "value_text": "string",
              "unit": "string",
              "source": "string"
            }
          ]
        },
        "metadata": {
          "property1": {
            "contact": {
              "name": "string",
              "email": "string",
              "organisation": "string"
            },
            "year_start": "string",
            "year_end": "string",
            "currency_rate": 0,
            "currency_code": "string",
            "sectors_covered": [
              "string"
            ],
            "reporting_organisations": {
              "companies": 0,
              "governmental_agencies": 0
            },
            "web_report_links": [
              {
                "url": "string",
                "title": "string",
                "attributes": []
              }
            ],
            "disaggregated": {
              "project": 0,
              "revenue_stream": 0,
              "company": 0
            }
          },
          "property2": {
            "contact": {
              "name": "string",
              "email": "string",
              "organisation": "string"
            },
            "year_start": "string",
            "year_end": "string",
            "currency_rate": 0,
            "currency_code": "string",
            "sectors_covered": [
              "string"
            ],
            "reporting_organisations": {
              "companies": 0,
              "governmental_agencies": 0
            },
            "web_report_links": [
              {
                "url": "string",
                "title": "string",
                "attributes": []
              }
            ],
            "disaggregated": {
              "project": 0,
              "revenue_stream": 0,
              "company": 0
            }
          }
        },
        "licenses": {
          "property1": {
            "property1": "string",
            "property2": "string"
          },
          "property2": {
            "property1": "string",
            "property2": "string"
          }
        },
        "contracts": {
          "property1": {
            "property1": "string",
            "property2": "string"
          },
          "property2": {
            "property1": "string",
            "property2": "string"
          }
        },
        "revenues": {
          "property1": {
            "government": 0,
            "company": 0
          },
          "property2": {
            "government": 0,
            "company": 0
          }
        },
        "latest_validation_date": "string",
        "latest_validation_link": "string",
        "latest_validation_url": "string"
      },
      "indicator_values": [
        {
          "id": 0,
          "label": "string",
          "self": "string",
          "value": 0,
          "unit": "string",
          "indicator": {
            "id": 0,
            "type": "string",
            "name": "string",
            "parent": 0,
            "status": 0,
            "created": 0
          }
        }
      ],
      "revenue_government": [
        {
          "id": 0,
          "type": "string",
          "gfs_code_id": 0,
          "report_status": 0,
          "name": "string",
          "organisation_id": 0,
          "revenue": 0,
          "currency": "string",
          "original_revenue": 0,
          "original_currency": "string"
        }
      ],
      "revenue_company": [
        {
          "id": 0,
          "type": "string",
          "gfs_code_id": 0,
          "report_status": 0,
          "name": "string",
          "organisation_id": 0,
          "revenue": 0,
          "currency": "string",
          "original_revenue": 0,
          "original_currency": "string"
        }
      ]
    }
  ],
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_summary_data_{id}-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_summary_data_{id}-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|integer|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» links|[string]|false|No description|
|»» email|string|false|No description|
|»» government_entities_nr|number|false|No description|
|»» company_entities_nr|number|false|No description|
|»» year_start|string|false|No description|
|»» year_end|string|false|No description|
|»» created|string|false|No description|
|»» changed|string|false|No description|
|»» sector_oil|integer|false|No description|
|»» sector_mining|integer|false|No description|
|»» sector_gas|integer|false|No description|
|»» sector_other|string|false|No description|
|»» report_file|string|false|No description|
|»» country|object|false|No description|
|»»» id|integer|false|No description|
|»»» label|string|false|No description|
|»»» self|string|false|No description|
|»»» iso2|string|false|No description|
|»»» iso3|string|false|No description|
|»»» status|object|false|No description|
|»»»» tid|integer|false|No description|
|»»»» language|string|false|No description|
|»»»» name|string|false|No description|
|»»»» color|string|false|No description|
|»»» status_date|integer|false|No description|
|»»» local_website|string|false|No description|
|»»» annual_report_file|string|false|No description|
|»»» reports|object|false|No description|
|»»»» **additionalProperties**|[object]|false|No description|
|»»»»» commodity|string|false|No description|
|»»»»» parent|string|false|No description|
|»»»»» id|integer|false|No description|
|»»»»» value|integer|false|No description|
|»»»»» value_bool|integer|false|No description|
|»»»»» value_text|string|false|No description|
|»»»»» unit|string|false|No description|
|»»»»» source|string|false|No description|
|»»»» metadata|object|false|No description|
|»»»»» **additionalProperties**|object|false|No description|
|»»»»»» contact|object|false|No description|
|»»»»»»» name|string|false|No description|
|»»»»»»» email|string|false|No description|
|»»»»»»» organisation|string|false|No description|
|»»»»»» year_start|string|false|No description|
|»»»»»» year_end|string|false|No description|
|»»»»»» currency_rate|number|false|No description|
|»»»»»» currency_code|string|false|No description|
|»»»»»» sectors_covered|[string]|false|No description|
|»»»»»» reporting_organisations|object|false|No description|
|»»»»»»» companies|integer|false|No description|
|»»»»»»» governmental_agencies|integer|false|No description|
|»»»»»» web_report_links|[object]|false|No description|
|»»»»»»» url|string|false|No description|
|»»»»»»» title|string|false|No description|
|»»»»»»» attributes|array|false|No description|
|»»»»»» disaggregated|object|false|No description|
|»»»»»»» project|integer|false|No description|
|»»»»»»» revenue_stream|integer|false|No description|
|»»»»»»» company|integer|false|No description|
|»»»»»» licenses|object|false|No description|
|»»»»»»» **additionalProperties**|object|false|No description|
|»»»»»»»» **additionalProperties**|string|false|No description|
|»»»»»»» contracts|object|false|No description|
|»»»»»»»» **additionalProperties**|object|false|No description|
|»»»»»»»»» **additionalProperties**|string|false|No description|
|»»»»»»»» revenues|object|false|No description|
|»»»»»»»»» **additionalProperties**|object|false|No description|
|»»»»»»»»»» government|integer|false|No description|
|»»»»»»»»»» company|integer|false|No description|
|»»»»»»»»» latest_validation_date|string|false|No description|
|»»»»»»»»» latest_validation_link|string|false|No description|
|»»»»»»»»» latest_validation_url|string|false|No description|
|»»»»»»»» indicator_values|[object]|false|No description|
|»»»»»»»»» id|integer|false|No description|
|»»»»»»»»» label|string|false|No description|
|»»»»»»»»» self|string|false|No description|
|»»»»»»»»» value|integer|false|No description|
|»»»»»»»»» unit|string|false|No description|
|»»»»»»»»» indicator|object|false|No description|
|»»»»»»»»»» id|integer|false|No description|
|»»»»»»»»»» type|string|false|No description|
|»»»»»»»»»» name|string|false|No description|
|»»»»»»»»»» parent|integer|false|No description|
|»»»»»»»»»» status|integer|false|No description|
|»»»»»»»»»» created|integer|false|No description|
|»»»»»»»»» revenue_government|[object]|false|No description|
|»»»»»»»»»» id|integer|false|No description|
|»»»»»»»»»» type|string|false|No description|
|»»»»»»»»»» gfs_code_id|integer|false|No description|
|»»»»»»»»»» report_status|integer|false|No description|
|»»»»»»»»»» name|string|false|No description|
|»»»»»»»»»» organisation_id|integer|false|No description|
|»»»»»»»»»» revenue|number|false|No description|
|»»»»»»»»»» currency|string|false|No description|
|»»»»»»»»»» original_revenue|number|false|No description|
|»»»»»»»»»» original_currency|string|false|No description|
|»»»»»»»»» revenue_company|[object]|false|No description|
|»»»»»»»»»» id|integer|false|No description|
|»»»»»»»»»» type|string|false|No description|
|»»»»»»»»»» gfs_code_id|integer|false|No description|
|»»»»»»»»»» report_status|integer|false|No description|
|»»»»»»»»»» name|string|false|No description|
|»»»»»»»»»» organisation_id|integer|false|No description|
|»»»»»»»»»» revenue|number|false|No description|
|»»»»»»»»»» currency|string|false|No description|
|»»»»»»»»»» original_revenue|number|false|No description|
|»»»»»»»»»» original_currency|string|false|No description|
|»»»»»»»»» self|object|false|No description|
|»»»»»»»»»» title|string|false|No description|
|»»»»»»»»»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

<h1 id="EITI---API-documentation-Summary-Data-v2">Summary Data v2</h1>

## get__v2.0_summary_data

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v2.0/summary_data \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v2.0/summary_data HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v2.0/summary_data',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v2.0/summary_data',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v2.0/summary_data',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v2.0/summary_data', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v2.0/summary_data");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v2.0/summary_data", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v2.0/summary_data`

Summary data is EITI’s tool for collecting and publishing data from EITI Reports in structured way. The summary data files are excel files, which are filled out by our implementing countries using the Summary Data Template. The national secretariats submit one excel-file for every fiscal year covered by an EITI Report.

<h3 id="get__v2.0_summary_data-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|filter[links]|query|string|false|Allows to filter summary data by their links URL|
|filter[government_entities_nr]|query|integer|false|Allows to filter summary data by their government entities number|
|filter[company_entities_nr]|query|integer|false|Allows to filter summary data by their company entities number|
|filter[year_start]|query|string|false|Allows to filter summary data by their start date (YYYY-MM-DD)|
|filter[year_end]|query|string|false|Allows to filter summary data by their end date (YYYY-MM-DD)|
|filter[created]|query|string|false|Allows to filter summary data by their created date (ISO 8601 format, mismatch with display)|
|filter[changed]|query|string|false|Allows to filter summary data by their changed date (ISO 8601 format, mismatch with display)|
|filter[sector_oil]|query|integer|false|Allows to filter summary data by their oil sector (0, 1)|
|filter[sector_mining]|query|integer|false|Allows to filter summary data by their mining sector (0, 1)|
|filter[sector_gas]|query|integer|false|Allows to filter summary data by their gas sector (0, 1)|
|filter[sector_other]|query|string|false|Allows to filter summary data by their other sectors|
|filter[report_file]|query|integer|false|Allows to filter summary data by their report file id|
|filter[country]|query|string|false|Allows to filter summary data by their country id|
|filter[indicator_values]|query|integer|false|Allows to filter summary data by their indicator values id|
|filter[revenue_government]|query|integer|false|Allows to filter summary data by their government revenue id|
|filter[revenue_company]|query|integer|false|Allows to filter summary data by their company revenue id|
|filter[currency_rate]|query|number|false|Allows to filter summary data by their currency rate|
|filter[currency_code]|query|string|false|Allows to filter summary data by their currency code|
|filter[company_identifier_name]|query|string|false|Allows to filter summary data by their company identifier name|
|filter[company_identifier_name_register]|query|string|false|Allows to filter summary data by their company identifier name register|
|filter[company_identifier_register_url]|query|string|false|Allows to filter summary data by their company identifier register url|

> Example responses

```json
{
  "data": [
    {
      "id": "string",
      "label": "string",
      "self": "string",
      "links": [
        "string"
      ],
      "government_entities_nr": 0,
      "company_entities_nr": 0,
      "year_start": "string",
      "year_end": "string",
      "created": "string",
      "changed": "string",
      "sector_oil": true,
      "sector_mining": true,
      "sector_gas": true,
      "sector_other": "string",
      "report_file": "string",
      "country": "string",
      "indicator_values": [
        [
          "string"
        ]
      ],
      "revenue_government": [
        "string"
      ],
      "revenue_company": [
        "string"
      ],
      "contact": {
        "name": "string",
        "email": null
      },
      "currency_rate": 0,
      "currency_code": "string",
      "disaggregated": {
        "project": true,
        "revenue_stream": true,
        "company": true
      },
      "revenue_government_sum": 0,
      "revenue_company_sum": 0,
      "company_identifier_name": "string",
      "company_identifier_name_register": "string",
      "company_identifier_register_url": "string"
    }
  ],
  "count": 0,
  "self": {
    "title": "string",
    "href": "string"
  },
  "next": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v2.0_summary_data-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v2.0_summary_data-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|string|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» links|[string]|false|No description|
|»» government_entities_nr|number|false|No description|
|»» company_entities_nr|number|false|No description|
|»» year_start|string|false|No description|
|»» year_end|string|false|No description|
|»» created|string|false|No description|
|»» changed|string|false|No description|
|»» sector_oil|boolean|false|No description|
|»» sector_mining|boolean|false|No description|
|»» sector_gas|boolean|false|No description|
|»» sector_other|string|false|No description|
|»» report_file|string|false|No description|
|»» country|string|false|No description|
|»» indicator_values|[array]|false|No description|
|»» revenue_government|[string]|false|No description|
|»» revenue_company|[string]|false|No description|
|»» contact|object|false|No description|
|»»» name|string|false|No description|
|»»» email|any|false|No description|
|»» currency_rate|number|false|No description|
|»» currency_code|string|false|No description|
|»» disaggregated|object|false|No description|
|»»» project|boolean|false|No description|
|»»» revenue_stream|boolean|false|No description|
|»»» company|boolean|false|No description|
|»» revenue_government_sum|number|false|No description|
|»» revenue_company_sum|number|false|No description|
|»» company_identifier_name|string|false|No description|
|»» company_identifier_name_register|string|false|No description|
|»» company_identifier_register_url|string|false|No description|
|» count|integer|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|
|» next|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

## get__v2.0_summary_data_{id}

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v2.0/summary_data/{id} \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v2.0/summary_data/{id} HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v2.0/summary_data/{id}',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v2.0/summary_data/{id}',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v2.0/summary_data/{id}',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v2.0/summary_data/{id}', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v2.0/summary_data/{id}");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v2.0/summary_data/{id}", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v2.0/summary_data/{id}`

Fetches a single summary data entry. Summary data is EITI’s tool for collecting and publishing data from EITI Reports in structured way. The summary data files are excel files, which are filled out by our implementing countries using the Summary Data Template. The national secretariats submit one excel-file for every fiscal year covered by an EITI Report.

<h3 id="get__v2.0_summary_data_{id}-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|id|path|integer|false|No description|

> Example responses

```json
{
  "data": [
    {
      "id": "string",
      "label": "string",
      "self": "string",
      "links": [
        "string"
      ],
      "government_entities_nr": 0,
      "company_entities_nr": 0,
      "year_start": "string",
      "year_end": "string",
      "created": "string",
      "changed": "string",
      "sector_oil": true,
      "sector_mining": true,
      "sector_gas": true,
      "sector_other": "string",
      "report_file": "string",
      "country": "string",
      "indicator_values": [
        [
          "string"
        ]
      ],
      "revenue_government": [
        "string"
      ],
      "revenue_company": [
        "string"
      ],
      "contact": {
        "name": "string",
        "email": null
      },
      "currency_rate": 0,
      "currency_code": "string",
      "disaggregated": {
        "project": true,
        "revenue_stream": true,
        "company": true
      },
      "revenue_government_sum": 0,
      "revenue_company_sum": 0,
      "company_identifier_name": "string",
      "company_identifier_name_register": "string",
      "company_identifier_register_url": "string"
    }
  ],
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v2.0_summary_data_{id}-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v2.0_summary_data_{id}-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|string|false|No description|
|»» label|string|false|No description|
|»» self|string|false|No description|
|»» links|[string]|false|No description|
|»» government_entities_nr|number|false|No description|
|»» company_entities_nr|number|false|No description|
|»» year_start|string|false|No description|
|»» year_end|string|false|No description|
|»» created|string|false|No description|
|»» changed|string|false|No description|
|»» sector_oil|boolean|false|No description|
|»» sector_mining|boolean|false|No description|
|»» sector_gas|boolean|false|No description|
|»» sector_other|string|false|No description|
|»» report_file|string|false|No description|
|»» country|string|false|No description|
|»» indicator_values|[array]|false|No description|
|»» revenue_government|[string]|false|No description|
|»» revenue_company|[string]|false|No description|
|»» contact|object|false|No description|
|»»» name|string|false|No description|
|»»» email|any|false|No description|
|»» currency_rate|number|false|No description|
|»» currency_code|string|false|No description|
|»» disaggregated|object|false|No description|
|»»» project|boolean|false|No description|
|»»» revenue_stream|boolean|false|No description|
|»»» company|boolean|false|No description|
|»» revenue_government_sum|number|false|No description|
|»» revenue_company_sum|number|false|No description|
|»» company_identifier_name|string|false|No description|
|»» company_identifier_name_register|string|false|No description|
|»» company_identifier_register_url|string|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

<h1 id="EITI---API-documentation-Chart---Bubble">Chart - Bubble</h1>

## get__v1.0_bubble

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/bubble \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/bubble HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/bubble',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/bubble',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/bubble',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/bubble', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/bubble");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/bubble", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/bubble`

Returns all the bubble chart endpoints

> Example responses

```json
{
  "data": [
    {
      "id": "disbursed_revenues",
      "label": "string",
      "description": "string",
      "self": "string"
    }
  ],
  "count": 0,
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_bubble-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_bubble-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|string|false|No description|
|»» label|string|false|No description|
|»» description|string|false|No description|
|»» self|string|false|No description|
|» count|integer|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

#### Enumerated Values

|Property|Value|
|---|---|
|id|disbursed_revenues|

<aside class="success">
This operation does not require authentication
</aside>

## get__v1.0_bubble_disbursed_revenues

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/bubble/disbursed_revenues \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/bubble/disbursed_revenues HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/bubble/disbursed_revenues',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/bubble/disbursed_revenues',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/bubble/disbursed_revenues',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/bubble/disbursed_revenues', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/bubble/disbursed_revenues");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/bubble/disbursed_revenues", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/bubble/disbursed_revenues`

*Country’s disbursed revenues*

Revenue disbursed by the governmental agencies of a specific country

<h3 id="get__v1.0_bubble_disbursed_revenues-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|filter[country_iso]|query|string|false|Allows to filter the revenues disbursed which belong to certain country, by sending the country’s ISO code|

> Example responses

```json
{
  "data": [
    {
      "name": "string",
      "children": [
        {
          "name": "string",
          "children": [
            {
              "name": "string",
              "size": 0
            }
          ]
        }
      ]
    }
  ],
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_bubble_disbursed_revenues-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_bubble_disbursed_revenues-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» name|string|false|No description|
|»» children|[object]|false|No description|
|»»» name|string|false|No description|
|»»» children|[object]|false|No description|
|»»»» name|string|false|No description|
|»»»» size|number|false|No description|
|»»» self|object|false|No description|
|»»»» title|string|false|No description|
|»»»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

<h1 id="EITI---API-documentation-Chart---Grouped-Bar">Chart - Grouped Bar</h1>

## get__v1.0_grouped_bar

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/grouped_bar \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/grouped_bar HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/grouped_bar',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/grouped_bar',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/grouped_bar',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/grouped_bar', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/grouped_bar");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/grouped_bar", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/grouped_bar`

Returns all the grouped bar chart endpoints

> Example responses

```json
{
  "data": [
    {
      "id": "production",
      "label": "string",
      "description": "string",
      "self": "string"
    }
  ],
  "count": 0,
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_grouped_bar-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_grouped_bar-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|string|false|No description|
|»» label|string|false|No description|
|»» description|string|false|No description|
|»» self|string|false|No description|
|» count|integer|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

#### Enumerated Values

|Property|Value|
|---|---|
|id|production|
|id|production_per_country|
|id|external_per_country|

<aside class="success">
This operation does not require authentication
</aside>

## get__v1.0_grouped_bar_production

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/grouped_bar/production \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/grouped_bar/production HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/grouped_bar/production',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/grouped_bar/production',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/grouped_bar/production',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/grouped_bar/production', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/grouped_bar/production");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/grouped_bar/production", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/grouped_bar/production`

*Global production for all countries per year*

Production volumes for all the countries

<h3 id="get__v1.0_grouped_bar_production-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|filter[year]|query|string|false|Allows to filter the production volumes per year|
|filter[indicator]|query|string|false|Allows to filter the production volumes per a certain set of indicator (by sending their IDs)|
|filter[country_iso]|query|string|false|Allows to filter the production volumes which belong to certain country, by sending the country’s ISO code|

> Example responses

```json
{
  "data": [
    {
      "name": "string",
      "x": [
        "string"
      ],
      "y": [
        0
      ]
    }
  ],
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_grouped_bar_production-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_grouped_bar_production-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» name|string|false|No description|
|»» x|[string]|false|Countries|
|»» y|[number]|false|Production Volumes|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

## get__v1.0_grouped_bar_production_per_country

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/grouped_bar/production_per_country \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/grouped_bar/production_per_country HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/grouped_bar/production_per_country',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/grouped_bar/production_per_country',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/grouped_bar/production_per_country',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/grouped_bar/production_per_country', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/grouped_bar/production_per_country");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/grouped_bar/production_per_country", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/grouped_bar/production_per_country`

*Country production for all of the years*

Production volumes

<h3 id="get__v1.0_grouped_bar_production_per_country-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|filter[year]|query|string|false|Allows to filter the production volumes per year|
|filter[indicator]|query|string|false|Allows to filter the production volumes per a certain set of indicator (by sending their IDs)|
|filter[country_iso]|query|string|false|Allows to filter the production volumes which belong to certain country, by sending the country’s ISO code|

> Example responses

```json
{
  "data": [
    {
      "name": "string",
      "x": [
        0
      ],
      "y": [
        0
      ]
    }
  ],
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_grouped_bar_production_per_country-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_grouped_bar_production_per_country-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» name|string|false|No description|
|»» x|[integer]|false|Years|
|»» y|[integer]|false|Production Volumes for all the Reported Years|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

## get__v1.0_grouped_bar_external_per_country

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/grouped_bar/external_per_country \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/grouped_bar/external_per_country HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/grouped_bar/external_per_country',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/grouped_bar/external_per_country',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/grouped_bar/external_per_country',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/grouped_bar/external_per_country', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/grouped_bar/external_per_country");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/grouped_bar/external_per_country", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/grouped_bar/external_per_country`

*Country’s external indicators for all of the years*

External indicators for all the reported years

<h3 id="get__v1.0_grouped_bar_external_per_country-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|filter[year]|query|string|false|Allows to filter the production volumes per year|
|filter[indicator]|query|string|false|Allows to filter the production volumes per a certain set of indicator (by sending their IDs)|
|filter[country_iso]|query|string|false|Allows to filter the production volumes which belong to certain country, by sending the country’s ISO code|

> Example responses

```json
{
  "data": [
    {
      "name": "string",
      "x": [
        0
      ],
      "y": [
        0
      ]
    }
  ],
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_grouped_bar_external_per_country-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_grouped_bar_external_per_country-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» name|string|false|No description|
|»» x|[integer]|false|Years|
|»» y|[integer]|false|USD|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

<h1 id="EITI---API-documentation-Chart---Sankey">Chart - Sankey</h1>

## get__v1.0_sankey

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/sankey \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/sankey HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/sankey',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/sankey',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/sankey',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/sankey', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/sankey");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/sankey", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/sankey`

Returns all the sankey chart endpoints

> Example responses

```json
{
  "data": [
    {
      "id": "disbursed_by_companies_per_country",
      "label": "string",
      "description": "string",
      "self": "string"
    }
  ],
  "count": 0,
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_sankey-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_sankey-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|string|false|No description|
|»» label|string|false|No description|
|»» description|string|false|No description|
|»» self|string|false|No description|
|» count|integer|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

#### Enumerated Values

|Property|Value|
|---|---|
|id|disbursed_by_companies_per_country|

<aside class="success">
This operation does not require authentication
</aside>

## get__v1.0_sankey_disbursed_by_companies_per_country

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/sankey/disbursed_by_companies_per_country \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/sankey/disbursed_by_companies_per_country HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/sankey/disbursed_by_companies_per_country',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/sankey/disbursed_by_companies_per_country',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/sankey/disbursed_by_companies_per_country',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/sankey/disbursed_by_companies_per_country', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/sankey/disbursed_by_companies_per_country");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/sankey/disbursed_by_companies_per_country", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/sankey/disbursed_by_companies_per_country`

*Country’s disbursed revenues by companies*

Revenue disbursed by companies of a specific country

<h3 id="get__v1.0_sankey_disbursed_by_companies_per_country-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|filter[country_iso]|query|string|false|Allows to filter the production volumes which belong to certain country, by sending the country’s ISO code|
|filter[years_from]|query|string|false|Allows to filter the production volumes starting with a certain year|
|filter[years_to]|query|string|false|Allows to filter the production volumes ending with a certain year|

> Example responses

```json
{
  "data": {
    "nodes": [
      {
        "name": "string",
        "type": "string"
      }
    ],
    "links": [
      {
        "source": 0,
        "target": 0,
        "value": 0
      }
    ]
  },
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_sankey_disbursed_by_companies_per_country-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_sankey_disbursed_by_companies_per_country-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|object|false|No description|
|»» nodes|[object]|false|No description|
|»»» name|string|false|No description|
|»»» type|string|false|No description|
|»» links|[object]|false|No description|
|»»» source|integer|false|No description|
|»»» target|integer|false|No description|
|»»» value|number|false|No description|
|»» self|object|false|No description|
|»»» title|string|false|No description|
|»»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>

<h1 id="EITI---API-documentation-Chart---Stacked-Bar">Chart - Stacked Bar</h1>

## get__v1.0_stacked_bar

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/stacked_bar \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/stacked_bar HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/stacked_bar',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/stacked_bar',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/stacked_bar',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/stacked_bar', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/stacked_bar");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/stacked_bar", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/stacked_bar`

Returns all the stacked bar chart endpoints

> Example responses

```json
{
  "data": [
    {
      "id": "government_revenues",
      "label": "string",
      "description": "string",
      "self": "string"
    }
  ],
  "count": 0,
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_stacked_bar-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_stacked_bar-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» id|string|false|No description|
|»» label|string|false|No description|
|»» description|string|false|No description|
|»» self|string|false|No description|
|» count|integer|false|No description|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

#### Enumerated Values

|Property|Value|
|---|---|
|id|government_revenues|

<aside class="success">
This operation does not require authentication
</aside>

## get__v1.0_stacked_bar_government_revenues

> Code samples

```shell
# You can also use wget
curl -X GET https://eiti.org/api/v1.0/stacked_bar/government_revenues \
  -H 'Accept: application/json'

```

```http
GET https://eiti.org/api/v1.0/stacked_bar/government_revenues HTTP/1.1
Host: eiti.org

Accept: application/json

```

```javascript
var headers = {
  'Accept':'application/json'

};

$.ajax({
  url: 'https://eiti.org/api/v1.0/stacked_bar/government_revenues',
  method: 'get',

  headers: headers,
  success: function(data) {
    console.log(JSON.stringify(data));
  }
})

```

```javascript--nodejs
const request = require('node-fetch');

const headers = {
  'Accept':'application/json'

};

fetch('https://eiti.org/api/v1.0/stacked_bar/government_revenues',
{
  method: 'GET',

  headers: headers
})
.then(function(res) {
    return res.json();
}).then(function(body) {
    console.log(body);
});

```

```ruby
require 'rest-client'
require 'json'

headers = {
  'Accept' => 'application/json'
}

result = RestClient.get 'https://eiti.org/api/v1.0/stacked_bar/government_revenues',
  params: {
  }, headers: headers

p JSON.parse(result)

```

```python
import requests
headers = {
  'Accept': 'application/json'
}

r = requests.get('https://eiti.org/api/v1.0/stacked_bar/government_revenues', params={

}, headers = headers)

print r.json()

```

```java
URL obj = new URL("https://eiti.org/api/v1.0/stacked_bar/government_revenues");
HttpURLConnection con = (HttpURLConnection) obj.openConnection();
con.setRequestMethod("GET");
int responseCode = con.getResponseCode();
BufferedReader in = new BufferedReader(
    new InputStreamReader(con.getInputStream()));
String inputLine;
StringBuffer response = new StringBuffer();
while ((inputLine = in.readLine()) != null) {
    response.append(inputLine);
}
in.close();
System.out.println(response.toString());

```

```go
package main

import (
       "bytes"
       "net/http"
)

func main() {

    headers := map[string][]string{
        "Accept": []string{"application/json"},
        
    }

    data := bytes.NewBuffer([]byte{jsonReq})
    req, err := http.NewRequest("GET", "https://eiti.org/api/v1.0/stacked_bar/government_revenues", data)
    req.Header = headers

    client := &http.Client{}
    resp, err := client.Do(req)
    // ...
}

```

`GET /v1.0/stacked_bar/government_revenues`

*Country governmental revenue*

Revenue disclosed by a government of a specific country.

<h3 id="get__v1.0_stacked_bar_government_revenues-parameters">Parameters</h3>

|Parameter|In|Type|Required|Description|
|---|---|---|---|---|
|filter[gfs_code]|query|string|false|Allows to filter the revenues which belong to certain GFS codes.|
|filter[country_iso]|query|string|false|Allows to filter the revenues which belong to certain country, by sending the country’s ISO code|

> Example responses

```json
{
  "data": [
    {
      "name": "string",
      "x": [
        0
      ],
      "y": [
        0
      ]
    }
  ],
  "self": {
    "title": "string",
    "href": "string"
  }
}
```

<h3 id="get__v1.0_stacked_bar_government_revenues-responses">Responses</h3>

|Status|Meaning|Description|Schema|
|---|---|---|---|
|200|[OK](https://tools.ietf.org/html/rfc7231#section-6.3.1)|OK|Inline|

<h3 id="get__v1.0_stacked_bar_government_revenues-responseschema">Response Schema</h3>

Status Code **200**

|Name|Type|Required|Description|
|---|---|---|---|
|» data|[object]|false|No description|
|»» name|string|false|No description|
|»» x|[integer]|false|Years|
|»» y|[number]|false|Government Revenue (normalized to USD)|
|» self|object|false|No description|
|»» title|string|false|No description|
|»» href|string|false|No description|

<aside class="success">
This operation does not require authentication
</aside>


