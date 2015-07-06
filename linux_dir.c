/*
 *
 *  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
 *
 *  By downloading, copying, installing or using the software you agree to this license.
 *  If you do not agree to this license, do not download, install,
 *  Copy or use the software.
 *
 *  Copyright (C) 2012, JUAN, Co, All Rights Reserved.
 *
 *  Created on: Jul 6, 2015
 *	Author: Frank Law
 *
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>

void foreach_dir(char *path, int depth)
{
	DIR *Dir;
	struct stat statbuf;
	char whole_path[1024];
	struct dirent *Entry = NULL;

	// Init Root Path
	snprintf(whole_path, sizeof(whole_path), "%s", path);

	Dir = opendir(whole_path);
	if (!Dir)
	{
		fprintf(stderr, "Cannot Open Directory \"%s\"\n", path);
		return;
	}

	while (NULL != (Entry = readdir(Dir)))
	{
		if (0 == strcmp(".", Entry->d_name) || 0 == strcmp("..", Entry->d_name))
		{
			continue;
		}
		else
		{
			char sub_path[1024];
			snprintf(sub_path, sizeof(sub_path), "%s/%s", whole_path,
					Entry->d_name);

			if (Entry->d_type & DT_DIR)
			{
				printf("Folder: \"%s\"\r\n", sub_path);

				if (0 == depth || depth > 1)
				{
					foreach_dir(sub_path, depth > 1 ? depth - 1 : depth);
				}
			}
			else if (Entry->d_type & DT_BLK)
			{
				printf("Block Device: \"%s\"\r\n", sub_path);
			}
			else if (Entry->d_type & DT_CHR)
			{
				printf("Character Device: \"%s\"\r\n", sub_path);
			}
			else if (Entry->d_type & DT_FIFO)
			{
				printf("Named PIPE: \"%s\"\r\n", sub_path);
			}
			else if (Entry->d_type & DT_LNK)
			{
				printf("Symbolic Link: \"%s\"\r\n", sub_path);
			}
			else if (Entry->d_type & DT_REG)
			{
				printf("Regular File: \"%s\"\r\n", sub_path);
			}
			else if (Entry->d_type & DT_SOCK)
			{
				printf("UNIX Domain Socket: \"%s\"\r\n", sub_path);
			}
			else if (Entry->d_type & DT_UNKNOWN)
			{
				printf("Unknow File: \"%s\"\r\n", sub_path);
			}
		}
	}

	closedir(Dir);
}

int main()
{
	printf("Directory scan of /home:\n");
	foreach_dir("/dev", 2);
	printf("done.\n");
	return 0;

}
