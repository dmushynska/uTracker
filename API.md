# API

### Authorisation part

#### Log In using Tokens

**Request for `Google oAuth2` from client to server**
```json
{
    "type": AUTO_OAUTH,
    "token": str SHA-256 hash,
}
```

**Successful response**
```json
{
    "type": AUTO_OAUTH,
    "message": str,
}
```

**Error response**
```json
{
    "type": AUTO_OAUTH,
    "error": num,
    "message": str,
}
```

**Request from client to server**
```json
{
    "type": AUTO_AUTH,
    "token": str SHA-256 hash,
}
```

**Successful response**
```json
{
    "type": AUTO_AUTH,
    "token": str SHA-256 hash,
    "message": str,
}
```

**Error response**
```json
{
    "type": AUTO_AUTH,
    "error": num,
    "message": str,
}
```

#### Sign Up

**Request from client to server**
```json
{
    "type": SIGN_UP,
    "email": str,
    "password": str SHA-256 hash,
    "name": str,
    "surname": str,
}
```

**Successful response**
```json
{
    "type": SIGN_UP,
    "token": str SHA-256 hash,
    "message": str,
}
```

**Error response**
```json
{
    "type": SIGN_UP,
    "error": num,
    "message": str,
}
```

#### Sign In

**Request from client to server**
```json
{
    "type": SIGN_IN,
    "email": str,
    "password": str SHA-256 hash,
}
```

**Successful response**
```json
{
    "type": SIGN_IN,
    "token": str SHA-256 hash,
    "message": str,
}
```

**Error response**
```json
{
    "type": SIGN_IN,
    "error": num,
    "message": str,
}
```
___