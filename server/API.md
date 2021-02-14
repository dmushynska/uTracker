```
enum class RequestType {
    SIGN_UP,
    SIGN_IN,
    AUTO_AUTH,
    AUTO_OAUTH,
    LOG_OUT,
    CREATE_WORKFLOW,
    UPDATE_WORKFLOW,
    INVITE_TO_WORKFLOW,
    GET_ALL_WORKFLOWS,
    GET_SINGLE_WORKFLOW_DATA,
    GET_STATISTICS,
    GET_PROFILE,
    UPDATE_PROFILE
};
```
***
# API

**Request for `Log Out` from client to server**
```json
{
    "type": LOG_OUT,
    "userId": num,
    "token": str SHA-256 hash
}
```

**Successful response**
```json
{
    "type": LOG_OUT,
    "message": str
}
```

**Error response**
```json
{
    "type": LOG_OUT,
    "error": num,
    "message": str
}
```
***
**Request for `CREATE_WORKFLOW` from client to server**
```json
{
    "type": CREATE_WORKFLOW,
    "title": str,
    "description": str,
    "ownerId" : num
    "token": str SHA-256 hash
}
```

**Successful response**
```json
{
    "type": CREATE_WORKFLOW,
    "message": str,
    "workflowId": num
}
```

**Error response**
```json
{
    "type": CREATE_WORKFLOW,
    "error": num,
    "message": str
}
```
***
**Request for `UPDATE_WORKFLOW` from client to server**
```json
{
    "type": UPDATE_WORKFLOW,
    "workflowId": num,
    "title": str,
    "description": str,
    "token": str SHA-256 hash
}
```

**Successful response**
```json
{
    "type": UPDATE_WORKFLOW,
    "message": str
}
```

**Error response**
```json
{
    "type": UPDATE_WORKFLOW,
    "error": num,
    "message": str
}
```

***
**Request for `GET_ALL_WORKFLOWS` from client to server**
```json
{
    "type": GET_ALL_WORKFLOWS
}
```

**Successful response**
```json
{
    "type": GET_ALL_WORKFLOWS,
    "message": str
    "allWorkflows" : {
                         "workflowId": num,
                         "title": str,
                         "description": str,
                         "userId" : num //
                     }
}
```

**Error response**
```json
{
    "type": GET_ALL_WORKFLOWS,
    "error": num,
    "message": str
}
```
***
**Request for `GET_SINGLE_WORKFLOW_DATA` from client to server**
```json
{
    "type": GET_SINGLE_WORKFLOW_DATA,
    "workflowId": num
}
```

**Successful response**
```json
{
    "type": GET_SINGLE_WORKFLOW_DATA,
    "message": str,
    "title": str,
    "description": str,
    "userId" : num //
}
```

**Error response**
```json
{
    "type": GET_SINGLE_WORKFLOW_DATA,
    "error": num,
    "message": str
}
```
***
**Request for `GET_STATISTICS` from client to server**
```json
{
    "type": GET_STATISTICS
}
```

**Successful response**
```json
{
    "type": GET_STATISTICS,
    "message": str,
    "workflowQuantity" : num,
    "TaskQuantity" : num,
    "userQuantity" : num
}
```

**Error response**
```json
{
    "type": GET_STATISTICS,
    "error": num,
    "message": str
}
```    
***
**Request for `GET_PROFILE` from client to server**
```json
{
    "type": GET_PROFILE,
    "userID" : num
}
```

**Successful response**
```json
{
    "type": GET_PROFILE,
    "message": str,
    "name" : str,
    "surname" : str
}
```

**Error response**
```json
{
    "type": GET_PROFILE,
    "error": num,
    "message": str
}
```
***
**Request for `UPDATE_PROFILE` from client to server**
```json
{
    "type": UPDATE_PROFILE,
    "userID" : num,
    "name" : str,
    "surname" : str
}
```

**Successful response**
```json
{
    "type": UPDATE_PROFILE,
    "message": str
}
```

**Error response**
```json
{
    "type": UPDATE_PROFILE,
    "error": num,
    "message": str
}
```
