/****************************************************************************
 * libs/libc/obstack/lib_obstack_vprintf.c
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

#include <stdio.h>
#include <assert.h>
#include <nuttx/streams.h>

/****************************************************************************
 * Private Types
 ****************************************************************************/

struct outstream
{
  struct lib_outstream_s public;
  FAR struct obstack *h;
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static int lib_puts(FAR struct lib_outstream_s *this,
    FAR const void *buf, int len)
{
  FAR struct outstream *mthis = (FAR struct outstream *)this;
  int ncopy;

  DEBUGASSERT(this);

  obstack_grow(mthis->h, buf, len);

  return len;
}

static void lib_putc(FAR struct lib_outstream_s *this, int ch)
{
  char tmp = ch;
  lib_puts(this, &tmp, 1);
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

int obstack_vprintf(FAR struct obstack *h, FAR const char *fmt, va_list ap)
{
  struct outstream outstream;

  outstream.public.put = lib_putc;
  outstream.public.puts = lib_puts;
  outstream.public.flush = lib_noflush;
  outstream.public.nput = 0;
  outstream.h = h;

  return lib_vsprintf(&outstream, fmt, ap);
}
