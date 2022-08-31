/****************************************************************************
 * libs/libc/obstack/lib_obstack_finish.c
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
#include <assert.h>

/****************************************************************************
 * Public Functions
 ****************************************************************************/

FAR void *obstack_finish (FAR struct obstack *h)
{
  size_t chsize;

  if (((void *)h->chunk + sizeof(struct _obstack_chunk)) == h->object_base)
    {
      chsize = h->next_free - (char *)h->chunk;
      h->chunk = realloc(h->chunk, chsize);
      h->chunk->limit = (void *)h->chunk + chsize;
      h->object_base = h->chunk->limit;
      h->next_free = h->chunk->limit;
      return (void *)h->chunk + sizeof(struct _obstack_chunk);
    }

  return obstack_finish_norealloc(h);
}

FAR void *obstack_finish_norealloc (FAR struct obstack *h)
{
  char *res = h->object_base;
  h->object_base = h->next_free;
  return res;
}
