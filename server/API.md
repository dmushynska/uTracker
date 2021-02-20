```
enum class RequestType {
    SIGN_UP,
    SIGN_IN,
    AUTO_AUTH,
    AUTO_OAUTH,
    LOG_OUT,
    CREATE_WORKFLOW,
    ARCHIVE_WORKFLOW,
    UPDATE_WORKFLOW,
    INVITE_TO_WORKFLOW,
    GET_ALL_WORKFLOWS,
    GET_SINGLE_WORKFLOW_DATA,
    GET_STATISTICS,
    GET_PROFILE,
    UPDATE_PROFILE, 
    CREATE_LIST,
    REMOVE_LIST,
    CREATE_TASK,
    UPDATE_TASK,
    MOVE_TASK,
    REMOVE_TASK,
    GET_TASK_DATA
};
```
***
# API

**Request for `SIGN UP` from client to server**
```json
{
    "type": SIGN_UP,
    "email": str,
    "login": str,
    "password": str,
    "name": str,
    "surname": str
}
```

**Successful response**
```json
{
    "type": SIGN_UP,
    "message": str,
    "token": str SHA-256 hash
    "userId": num
}
```
**Error response**
```json
{
    "type": SIGN_UP,
    "error": num,
    "message": str
}
```

***

**Request for `SIGN_IN` from client to server**
```json
{
    "type": SIGN_IN,
    "login": str, // or email in "login"
    "password": str, SHA-256 hash
    "token": str SHA-256 hash
}
```

**Successful response**
```json
{
    "type": SIGN_IN,
    "message": str,
    "token": str,
    "userId": num,
    "login": str,
    "email": str,
    "name": str,
    "surname": str
}
```
**Error response**
```json
{
    "type": SIGN_IN,
    "error": num,
    "message": str
}
```

***

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
    "type" : CREATE_WORKFLOW,
    "title" : str,
    "deadline" : str,
    "ownerId" : num
    "token" : str SHA-256 hash
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

////
***

**Request for `ARCHIVE_WORKFLOW` from client to server**
```json
{
    "type": ARCHIVE_WORKFLOW,
    "workflowId" : num,
    "token": str SHA-256 hash
}
```

**Successful response**
```json
{
    "type": ARCHIVE_WORKFLOW,
    "message": str
}
```

**Error response**
```json
{
    "type": ARCHIVE_WORKFLOW,
    "error": num,
    "message": str
}
```

***
**Request for `UPDATE_WORKFLOW` from client to server**
```json
{
    "type" : UPDATE_WORKFLOW,
    "workflowId" : num,
    "title" : str,
    "deadline" : str,
    "token" : str SHA-256 hash
}
```

**Successful response**
```json
{
    "type": UPDATE_WORKFLOW,
    "title": str,
    "deadline": str,
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

**Request for `INVITE TO WORKFLOW` from client to server**
```json
{
    "type": INVITE_TO_WORKFLOW,
    "workflowId" : num,
    "login" : str,
    "token" : str SHA-256 hash
}
```

**Successful response**
```json
{
    "type": INVITE_TO_WORKFLOW,
    "message": str
}
```

**Error response**
```json
{
    "type": INVITE_TO_WORKFLOW,
    "error": num,
    "message": str
}
```

***
**Request for `GET_ALL_WORKFLOWS` from client to server**
```json
{
    "type": GET_ALL_WORKFLOWS,
    "userId": num,
    "token" : str SHA-256 hash
}
```

**Successful response**
```json
{
    "type": GET_ALL_WORKFLOWS,
    "message": str
    "allWorkflows" : {
                         "type": GET_SINGLE_WORKFLOW_DATA,
                         "message": str,
                         "workflowId": num,
                         "title": str,
                         "deadline": str,
                         "ownerId" : num //
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
    "workflowId": num,
    "token" : str SHA-256 hash
}
```

**Successful response**
```json
{
    "type": GET_SINGLE_WORKFLOW_DATA,
    "message": str,
    "workflowId": num,
    "title": str,
    "deadline": str,
    "ownerId" : num //
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
    "type": GET_STATISTICS,
    "token" : str SHA-256 hash
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
    "userId" : num,
    "token" : str SHA-256 hash
}
```

**Successful response**
```json
{
    "type": GET_PROFILE,
    "message": str,
    "login": str,
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
    "surname" : str,
    "token" : str SHA-256 hash
}
```

**Successful response**
```json
{
    "type": UPDATE_PROFILE,
    "message": str,
    "name" : str,
    "surname" : str
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

***
**Request for `CREATE_LIST` from client to server**
```json
{
    "type": CREATE_LIST,
    "workflowId" : num,
    "title" : str,
    "token" : str SHA-256 hash
}
```

**Successful response**
```json
{
    "type": CREATE_LIST,
    "message": str,
    "listId" : num
}
```

**Error response**
```json
{
    "type": CREATE_LIST,
    "error": num,
    "message": str
}
```

***
**Request for `REMOVE_LIST` from client to server**
```json
{
    "type": REMOVE_LIST,
    "listId" : num,
    "token" : str SHA-256 hash
}
```

**Successful response**
```json
{
    "type": REMOVE_LIST,
    "message": str
}
```

**Error response**
```json
{
    "type": REMOVE_LIST,
    "error": num,
    "message": str
}
```

***
**Request for `CREATE_TASK` from client to server**
```json
{
    "type": CREATE_TASK,
    "listId" : num,
    "title": str,
    "token" : str SHA-256 hash
}
```

**Successful response**
```json
{
    "type": CREATE_TASK,
    "message": str,
    "taskId" : num
}
```

**Error response**
```json
{
    "type": CREATE_TASK,
    "error": num,
    "message": str
}
```

***
**Request for `UPDATE_TASK` from client to server**
```json
{
    "type": UPDATE_TASK,
    "taskId" : num,
    "description": str,
    "checkList": qvariant,
    "token" : str SHA-256 hash
}
```

**Successful response**
```json
{
    "type": UPDATE_TASK,
    "message": str,
    "description": str,
    "checkList": qvariant
}
```

**Error response**
```json
{
    "type": UPDATE_TASK,
    "error": num,
    "message": str
}
```

***
**Request for `MOVE_TASK` from client to server**
```json
{
    "type": MOVE_TASK,
    "taskId" : num,
    "newListId" : num,
    "newIndexId" : num,
    "token" : str SHA-256 hash
}
```

**Successful response**
```json
{
    "type": MOVE_TASK,
    "message": str
}
```

**Error response**
```json
{
    "type": MOVE_TASK,
    "error": num,
    "message": str
}
```

***
**Request for `REMOVE_TASK` from client to server**
```json
{
    "type": REMOVE_TASK,
    "taskId" : num,
    "token" : str SHA-256 hash
}
```

**Successful response**
```json
{
    "type": REMOVE_TASK,
    "message": str
}
```

**Error response**
```json
{
    "type": REMOVE_TASK,
    "error": num,
    "message": str
}
```

***
**Request for `GET_TASK_DATA` from client to server**
```json
{
    "type": GET_TASK_DATA,
    "taskId" : num,
    "token" : str SHA-256 hash
}
```

**Successful response**
```json
{
    "type": GET_TASK_DATA,
    "message": str,
    "description": str,
    "checkList": str // Назар разбивает на свои штуки)
}
```

**Error response**
```json
{
    "type": GET_TASK_DATA,
    "error": num,
    "message": str
}
```
