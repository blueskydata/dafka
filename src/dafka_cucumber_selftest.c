/*  =========================================================================
    dafka_cucumber_selftest.c - run cucumber selftests

    Runs cucumber steps servers and cucumber feature runner in one process

    -------------------------------------------------------------------------
    Copyright (c) the Contributors as noted in the AUTHORS file. This
    file is part of DAFKA, a decentralized distributed streaming
    platform: http://zeromq.org.

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.

################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################
    =========================================================================
*/

#include "dafka_classes.h"
#if defined (HAVE_CUCUMBER)
#include <cucumber_c.h>

int main (int argc, char *argv [])
{
    zargs_t *args = zargs_new (argc, argv);
    zsock_t *client = zsock_new_dealer (">tcp://127.0.0.1:8888");
    assert (client);
    zclock_sleep (250);
    zlist_t *step_runners = zlist_new ();

    CREATE_STEP_RUNNER_ACTOR(dafka_consumer, consumer_protocol_state_new, consumer_protocol_state_destroy)
    zlist_append (step_runners, dafka_consumer_steps_runner);


    const char *filename = zargs_first (args);
    cucumber_feature_runner_t *feature_runner = cucumber_feature_runner_new (filename);
    bool rc = cucumber_feature_runner_run (feature_runner, client);

    zactor_t *step_runner = (zactor_t *) zlist_first (step_runners);
    while (step_runner != NULL) {
        zstr_send (step_runner, "$TERM");
        zactor_destroy (&step_runner);
    }

    zargs_destroy (&args);
    zlist_destroy (&step_runners);;
    zsock_destroy (&client);
    cucumber_feature_runner_destroy (&feature_runner);
    return rc ? 0 : 1;
}
/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################
*/
#endif
