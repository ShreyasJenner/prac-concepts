#include <FLAC/format.h>
#include <FLAC/metadata.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  /* Declaration */
  FLAC__Metadata_SimpleIterator *itr;
  FLAC__MetadataType metatype;
  FLAC__StreamMetadata *metadata;

  /* Initialization */

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
  for (int i = 0; i < 2; i++) {
    FLAC__metadata_simple_iterator_next(itr);
  }
  metatype = FLAC__metadata_simple_iterator_get_block_type(itr);
  printf("Metatype: %d\n", metatype);

  /* Get block data */
  metadata = FLAC__metadata_simple_iterator_get_block(itr);
  if (metadata == NULL) {
    fprintf(stderr, "Error getting metadata block\n");
    exit(1);
  } else {
    printf("Metadata: %d\n", metadata->data.vorbis_comment.comments->length);
  }

  /* close the flac file */
  FLAC__metadata_simple_iterator_delete(itr);

  return 0;
}
