/****************************************************************************
 * libs/libc/obstack/lib_obstack_free.c
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <obstack.h>
#include <stdlib.h>

/****************************************************************************
 * Public Functions
 ****************************************************************************/

void obstack_free (FAR struct obstack *h, FAR void *object)
{
  FAR struct _obstack_chunk *prev;

  while (h->chunk)
    {
      if (object >= (void *)&h->chunk + sizeof(struct _obstack_chunk)
          && object < (void *)h->chunk->limit)
        {
          /* The obect is in this chunk so just move object base.
           * Note: this keeps the last chunk allocated. This is desirable
           * behavior as we can decide if we want to reuse it by either
           * passing NULL to free everything or the first returned object to
           * keep the chunk allocated.
           */

          h->object_base = object;
          h->next_free = object;
          return;
        }

      prev = h->chunk->prev;
      free(h->chunk);
      h->chunk = prev;
    }

  h->object_base = NULL;
  h->next_free = NULL;
}
