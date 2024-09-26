#include <FLAC/format.h>
#include <FLAC/metadata.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  /* Declaration */
  int ch;
  bool flag;

  FLAC__Metadata_SimpleIterator *itr;
  FLAC__MetadataType metatype;
  FLAC__StreamMetadata *metadata;

  /* check if file arg has been passed */
  if (argc < 2) {
    fprintf(stderr, "File arguments missing\n");
    exit(1);
  }

  itr = FLAC__metadata_simple_iterator_new();
  if (itr == NULL) {
    fprintf(stderr, "Error creating flac metadata iterator\n");
    exit(1);
  }

  /* open the flac file */
  if (FLAC__metadata_simple_iterator_init(itr, argv[1], true, false) == false) {
    fprintf(stderr, "Error creating flac metadata iterator\n");
    exit(1);
  }

  /* get block type */
  flag = true;
  while (flag) {
    scanf("%c", &ch);
    // printf("ch= %c\n", ch);
    getchar();
    switch (ch) {
    case 'n':
      if (FLAC__metadata_simple_iterator_next(itr) == true) {
        printf("Moving to next metadata block\n");
      } else {
        printf("At last block\n");
      }
      break;

    case 'p':
      metatype = FLAC__metadata_simple_iterator_get_block_type(itr);
      printf("Metatype: %d\n", metatype);

      metadata = FLAC__metadata_simple_iterator_get_block(itr);
      if (metadata == NULL) {
        fprintf(stderr, "Error getting metadata block\n");
        exit(1);
      }

      if (metatype == 0) {
        /* Stream info */
        printf("Stream Info\n");
        printf("Min Block size:%d\n", metadata->data.stream_info.min_blocksize);
        printf("Max Block size:%d\n", metadata->data.stream_info.max_blocksize);
        printf("Min Frame size:%d\n", metadata->data.stream_info.min_framesize);
        printf("Max Block size:%d\n", metadata->data.stream_info.max_framesize);
        printf("Sample rate:%d\n", metadata->data.stream_info.sample_rate);
        printf("Channels:%d\n", metadata->data.stream_info.channels);
        printf("Bits per sample:%d\n",
               metadata->data.stream_info.bits_per_sample);
        printf("Total Samples:%ld\n", metadata->data.stream_info.total_samples);
        printf("md5sum:%s\n", metadata->data.stream_info.md5sum);
      } else if (metatype == 1) {
        /* Padding */
        printf("Padding\n");
        printf("Dummy:%d\n", metadata->data.padding.dummy);
      } else if (metatype == 2) {
        /* Application */
        printf("Application\n");
        printf("Id: %s\n", metadata->data.application.id);
        printf("Data: %s\n", metadata->data.application.data);
      } else if (metatype == 3) {
        /* Seek Table */
        printf("Seek Table\n");
        printf("Num Points: %d\n", metadata->data.seek_table.num_points);
        printf("Seek Point sample number: %ld\n",
               metadata->data.seek_table.points->sample_number);
        printf("Seek Point stream offset: %ld\n",
               metadata->data.seek_table.points->stream_offset);
        printf("Seek Point frame samples: %d\n",
               metadata->data.seek_table.points->frame_samples);
      } else if (metatype == 4) {
        /* Vorbis Comment */
        printf("Vorbis Comment\n");
        printf("Vendor String Length:%d\n",
               metadata->data.vorbis_comment.vendor_string.length);
        printf("Vendor String Entry:%s\n",
               metadata->data.vorbis_comment.vendor_string.entry);
        printf("Num Comments: %d\n",
               metadata->data.vorbis_comment.num_comments);
        for (int i = 0; i < metadata->data.vorbis_comment.num_comments; i++) {
          printf("Vorbis Comment Length : %d\n",
                 metadata->data.vorbis_comment.comments[i].length);
          printf("Vorbis Comment Entry : %s\n",
                 metadata->data.vorbis_comment.comments[i].entry);
        }
      } else if (metatype == 5) {
        /* Cue Sheet */
        printf("Cue Sheet\n");
        printf("Media Catalog Number: %s\n",
               metadata->data.cue_sheet.media_catalog_number);
        printf("Lead in: %ld\n", metadata->data.cue_sheet.lead_in);
        printf("Is Cd: %b\n", metadata->data.cue_sheet.is_cd);
        printf("Num Tracks: %d\n", metadata->data.cue_sheet.num_tracks);

        printf("Cue Sheet Track\n");
        printf("Offset: %ld\n", metadata->data.cue_sheet.tracks->offset);
        printf("Number: %d\n", metadata->data.cue_sheet.tracks->number);
        printf("isrc: %s\n", metadata->data.cue_sheet.tracks->isrc);
        printf("type: %d\n", metadata->data.cue_sheet.tracks->type);
        printf("pre-emphasis: %d\n",
               metadata->data.cue_sheet.tracks->pre_emphasis);
        printf("Num Indices: %d\n",
               metadata->data.cue_sheet.tracks->num_indices);
        printf("Cue Sheet Index\n");
        printf("Offset: %ld\n",
               metadata->data.cue_sheet.tracks->indices->offset);
        printf("Number: %d\n",
               metadata->data.cue_sheet.tracks->indices->number);
      } else if (metatype == 6) {
        /* Picture */
        printf("Picture\n");
        printf("Mime type:%s\n", metadata->data.picture.mime_type);
        printf("Description: %s\n", metadata->data.picture.description);
        printf("Width: %d\n", metadata->data.picture.width);
        printf("Height: %d\n", metadata->data.picture.height);
        printf("Depth: %d\n", metadata->data.picture.depth);
        printf("Colors: %d\n", metadata->data.picture.colors);
        printf("Data Length: %d\n", metadata->data.picture.data_length);

        int fd = open("test.jpeg", O_WRONLY | O_CREAT, 0666);
        if (fd < 0) {
          fprintf(stderr, "Unable to open file\n");
          exit(1);
        }
        write(fd, metadata->data.picture.data,
              metadata->data.picture.data_length);
        close(fd);

        /* Unkown handling */
      } else if (metatype == 7) {
        printf("Unkown Block\n");
      }
      break;

    case 'q':
      printf("Quitting\n");
      flag = false;
      break;
    default:
      break;
    }
  }

  /* close the flac file */
  FLAC__metadata_simple_iterator_delete(itr);

  return 0;
}
