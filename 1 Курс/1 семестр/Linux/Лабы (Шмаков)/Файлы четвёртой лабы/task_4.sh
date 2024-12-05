#!/bin/bash

# Check if there are two arguments
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 catalog1 catalog2"
    exit 1
fi

# Assign names to directories
catalog=$1
catalog2=$2

echo "Comparing contents of directories $catalog and $catalog2"

# Compare file names in directories
echo "Differences in file names:"
diff -qr "$catalog" "$catalog2"

# Compare sizes of files
echo "Differences in file sizes:"
find "$catalog" -type f -exec ls -l {} + | awk '{print $5, $9}' > /tmp/catalog_sizes
find "$catalog2" -type f -exec ls -l {} + | awk '{print $5, $9}' > /tmp/catalog2_sizes
diff /tmp/catalog_sizes /tmp/catalog2_sizes

# Compare attributes of files
echo "Differences in file attributes: "

find "$catalog" -type f -exec stat --format="%n %s %a" {} + > /tmp/catalog_attrs
find "$catalog2" -type f -exec stat --format="%n %s %a" {} + > /tmp/catalog2_attrs
diff /tmp/catalog_attrs /tmp/catalog2_attrs