#pragma once
#include <stddef.h>
#include <mongoc.h>

int db_core_init(const char *db_path);
void db_core_deinit();

void db_core_refresh();

int db_input_validation(const char * str);

mongoc_client_t *mongo_client, *traffick_track_db_client;
