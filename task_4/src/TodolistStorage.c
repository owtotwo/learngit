#include <stdio.h> // for fopen, FILE, fseek, ftell, fclose, fread, fwrite, sprintf
#include <stdlib.h> // for malloc, free
#include <assert.h> // for assert
#include "TodolistStorage.h"
#include "TodolistErrorCode.h" // for error_t
#include "TodolistModel.h" // for todolist_t, item_node_t
#include "cJSON.h"

error_t todolist_save(todolist_t* tdl) {
    assert(tdl);
    FILE* fout = fopen(tdl->file_address, "wt");
    if (!fout) {
        perror("Saving...");
        return FAILURE;
    }
    
    cJSON *root, *data, *item;

    root = cJSON_CreateObject();

    cJSON_AddNumberToObject(root, "id_count", tdl->id_count);
    cJSON_AddItemToObject(root, "data", data = cJSON_CreateArray());

    item_node_t* p = tdl->item_list;
    while (p) {
        cJSON_AddItemToArray(data, item  = cJSON_CreateObject());
        cJSON_AddNumberToObject(item, "id", p->data->id);
        cJSON_AddNumberToObject(item, "state", p->data->state);
        cJSON_AddNumberToObject(item, "timestamp", p->data->timestamp);
        cJSON_AddStringToObject(item, "content", p->data->content);
        p = p->next;
    }

    char* out_buffer = cJSON_Print(root);
    cJSON_Delete(root);

    fprintf(fout, "%s\n", out_buffer);
    free(out_buffer);

    fclose(fout);

    return SUCCESS;
}

error_t todolist_load(todolist_t* tdl) {
    assert(tdl);
    FILE* fin = fopen(tdl->file_address, "rt");
    if (!fin) {
        perror("Loading");
        return FAILURE;
    }

    // reset the todolist
    destroy_item_list(&(tdl->item_list));
    create_item_list(&(tdl->item_list));
    tdl->id_count = 0;

    fseek(fin, 0, SEEK_END);
    int length = ftell(fin);
    fseek(fin, 0, SEEK_SET);

    char* buffer = (char*)malloc(length * sizeof(char) + 1);
    fread(buffer, sizeof(char), length, fin);
    buffer[length] = '\0';

    cJSON* json = cJSON_Parse(buffer);

    
    cJSON* data = cJSON_GetObjectItem(json, "data");

    assert(cJSON_HasObjectItem(json, "data"));
    assert(data);
    
    for (int i = 0; i < cJSON_GetArraySize(data); i++) {
        cJSON* item = cJSON_GetArrayItem(data, i);
        todolist_add_item(
            tdl,
            cJSON_GetObjectItem(item, "content")->valuestring,
            cJSON_GetObjectItem(item, "id")->valueint,
            cJSON_GetObjectItem(item, "state")->valueint,
            cJSON_GetObjectItem(item, "timestamp")->valueint
        );
    }

    tdl->id_count = cJSON_GetObjectItem(json, "id_count")->valueint;
    
    cJSON_Delete(json);
    
    return SUCCESS;
}