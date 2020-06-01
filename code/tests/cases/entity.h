MODULE(entity, {
    int8_t r = LIBRG_FAIL;

    IT("should be able to track and untrack an entity", {
        librg_world *world = librg_world_create();

        r = librg_entity_tracked(world, 15); EQUALS(r, LIBRG_FALSE);
        r = librg_entity_track(world, 15); EQUALS(r, LIBRG_OK);
        r = librg_entity_tracked(world, 15); EQUALS(r, LIBRG_TRUE);
        r = librg_entity_untrack(world, 15); EQUALS(r, LIBRG_OK);
        r = librg_entity_tracked(world, 15); EQUALS(r, LIBRG_FALSE);

        librg_world_destroy(world);
    });

    IT("should be able to properly set a userdata", {
        librg_world *world = librg_world_create();
        librg_entity_track(world, 15);

        r = librg_entity_userdata_set(world, 15, (void *)15); EQUALS(r, LIBRG_OK);
        r = (int)librg_entity_userdata_get(world, 15); EQUALS(r, 15);

        librg_entity_untrack(world, 15);
        librg_world_destroy(world);
    });

    // IT("should be able to properly set a type", {
    //     librg_world *world = librg_world_create();
    //     librg_entity_track(world, 15);

    //     r = librg_entity_type_set(world, 15, LIBRG_ENTITY_DYNAMIC); EQUALS(r, LIBRG_OK);
    //     r = librg_entity_type_get(world, 15); EQUALS(r, LIBRG_ENTITY_DYNAMIC);

    //     librg_entity_untrack(world, 15);
    //     librg_world_destroy(world);
    // });

    IT("should be able to properly set a chunk", {
        librg_world *world = librg_world_create();
        librg_entity_track(world, 15);

        r = librg_entity_chunk_set(world, 15, 15); EQUALS(r, LIBRG_OK);
        r = librg_entity_chunk_get(world, 15); EQUALS(r, 15);

        librg_entity_untrack(world, 15);
        librg_world_destroy(world);
    });

    IT("should be able to properly set an owner", {
        librg_world *world = librg_world_create();
        librg_entity_track(world, 15);

        r = librg_entity_owner_set(world, 15, 15); EQUALS(r, LIBRG_OK);
        r = librg_entity_owner_get(world, 15); EQUALS(r, 15);

        librg_entity_untrack(world, 15);
        librg_world_destroy(world);
    });

    IT("should be able to properly set a radius", {
        librg_world *world = librg_world_create();
        librg_entity_track(world, 15);

        r = librg_entity_radius_set(world, 15, 15); EQUALS(r, LIBRG_OK);
        r = librg_entity_radius_get(world, 15); EQUALS(r, 15);

        librg_entity_untrack(world, 15);
        librg_world_destroy(world);
    });

    IT("should be able to properly set a dimension", {
        librg_world *world = librg_world_create();
        librg_entity_track(world, 15);

        r = librg_entity_dimension_set(world, 15, 15); EQUALS(r, LIBRG_OK);
        r = librg_entity_dimension_get(world, 15); EQUALS(r, 15);

        librg_entity_untrack(world, 15);
        librg_world_destroy(world);
    });

    IT("should be able to properly set an array of chunks", {
        librg_world *world = librg_world_create();
        librg_entity_track(world, 15);

        librg_chunk arr[3]; arr[0] = 1; arr[1] = 2; arr[2] = 3;
        r = librg_entity_chunkarray_set(world, 15, arr, 3); EQUALS(r, LIBRG_OK);

        librg_chunk res[5];
        int amt = librg_entity_chunkarray_get(world, 15, res, 5);

        EQUALS(amt, 3);
        EQUALS(res[0], 1);
        EQUALS(res[1], 2);
        EQUALS(res[2], 3);

        librg_entity_untrack(world, 15);
        librg_world_destroy(world);
    });

    IT("should be able to properly set an array of chunks with overflow", {
        librg_world *world = librg_world_create();
        librg_entity_track(world, 15);

        librg_chunk arr[3]; arr[0] = 1; arr[1] = 2; arr[2] = 3;
        r = librg_entity_chunkarray_set(world, 15, arr, 3); EQUALS(r, LIBRG_OK);

        librg_chunk res[3] = {0};
        int amt = librg_entity_chunkarray_get(world, 15, res, 2);

        EQUALS(amt, 2);
        EQUALS(res[0], 1);
        EQUALS(res[1], 2);
        EQUALS(res[2], 0);

        librg_entity_untrack(world, 15);
        librg_world_destroy(world);
    });

    IT("should fail when attempting to set data onto untracked entity", {
        librg_world *world = librg_world_create();

        r = librg_entity_userdata_set(world, 15, (void *)15); NEQUALS(r, LIBRG_OK);
        // r = librg_entity_type_set(world, 15, LIBRG_ENTITY_DYNAMIC); NEQUALS(r, LIBRG_OK);
        r = librg_entity_chunk_set(world, 15, 15); NEQUALS(r, LIBRG_OK);
        r = librg_entity_owner_set(world, 15, 15); NEQUALS(r, LIBRG_OK);
        r = librg_entity_radius_set(world, 15, 15); NEQUALS(r, LIBRG_OK);
        r = librg_entity_dimension_set(world, 15, 15); NEQUALS(r, LIBRG_OK);

        librg_world_destroy(world);
    });
});
