/*
 * Copyright (c) 2007 The Regents of the University of California.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <opensm/osm_event_plugin.h>

/****h* OpenSM Event plugin interface
* DESCRIPTION
*       Database interface to record subnet events
*
*       Implementations of this object _MUST_ be thread safe.
*
* AUTHOR
*	Ira Weiny, LLNL
*
*********/

#include <stdlib.h>
#include <dlfcn.h>

#include <opensm/osm_event_plugin.h>

#if defined(PATH_MAX)
#define OSM_PATH_MAX	(PATH_MAX + 1)
#elif defined (_POSIX_PATH_MAX)
#define OSM_PATH_MAX	(_POSIX_PATH_MAX + 1)
#else
#define OSM_PATH_MAX	256
#endif

/**
 * functions
 */
osm_epi_plugin_t *
osm_epi_construct(osm_log_t *p_log, char *plugin_name)
{
	char              lib_name[OSM_PATH_MAX];
	osm_epi_plugin_t *rc = NULL;

	if (!plugin_name)
		return (NULL);

	/* find the plugin */
	snprintf(lib_name, OSM_PATH_MAX, "lib%s.so", plugin_name);

	rc = malloc(sizeof(*rc));
	if (!rc)
		return (NULL);

	rc->handle = dlopen(lib_name, RTLD_LAZY);
	if (!rc->handle) {
		osm_log(p_log, OSM_LOG_ERROR,
			"Failed to open event plugin \"%s\" : \"%s\"\n",
			lib_name, dlerror());
		goto DLOPENFAIL;
	}

	rc->impl = (__osm_epi_plugin_t *)dlsym(rc->handle, OSM_EVENT_PLUGIN_IMPL_NAME);
	if (!rc->impl) {
		osm_log(p_log, OSM_LOG_ERROR,
			"Failed to find \"%s\" symbol in \"%s\" : \"%s\"\n",
			OSM_EVENT_PLUGIN_IMPL_NAME,
			lib_name, dlerror());
		goto Exit;
	}

	/* Check the version to make sure this module will work with us */
	if (rc->impl->interface_version != OSM_EVENT_PLUGIN_INTERFACE_VER) {
		osm_log(p_log, OSM_LOG_ERROR,
			"%s symbol is the wrong version %d != %d\n",
			OSM_EVENT_PLUGIN_IMPL_NAME,
			rc->impl->interface_version,
			OSM_EVENT_PLUGIN_INTERFACE_VER);
		goto Exit;
	}

	if (!rc->impl->construct) {
		osm_log(p_log, OSM_LOG_ERROR,
			"%s symbol has no construct function\n",
			OSM_EVENT_PLUGIN_IMPL_NAME);
		goto Exit;
	}

	rc->plugin_data = rc->impl->construct(p_log);

	if (!rc->plugin_data)
		goto Exit;

	rc->p_log = p_log;
	return (rc);

Exit:
	dlclose(rc->handle);
DLOPENFAIL:
	free(rc);
	return (NULL);
}

void
osm_epi_destroy(osm_epi_plugin_t *plugin)
{
	if (plugin) {
		if (plugin->impl->destroy)
			plugin->impl->destroy(plugin->plugin_data);
		dlclose(plugin->handle);
		free(plugin);
	}
}

void
osm_epi_report(osm_epi_plugin_t *plugin, osm_epi_event_id_t event_id,
		void *event_data)
{
	if (plugin && plugin->impl->report)
		plugin->impl->report(plugin->plugin_data,
				event_id, event_data);
}
