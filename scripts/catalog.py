#
# Title: catalog.py
# Description: 
# 
#
import json
import time
import uuid

from datetime import datetime, timezone

class Catalog:

    def execute(self, file_name: str) -> None:
        catalog = {
            "antenna": "unknown",
            "application": "unknown",
            "duration": 0,
            "epoch_time": int(time.time()),
            "host": "unknown",
            "json_version": 1,
            "key": str(uuid.uuid4()),
            "note": "none",
            "receiver": "unknown",
            "sample_frequency": 0,
            "signal_frequency": 0,
            "site": "unknown",
            "time_stamp": datetime.now(timezone.utc).isoformat(),
        }

        file_name = f"{catalog['key']}.json"
        print(f"creating {file_name}")

        try:
            with open(file_name, "w") as out_file:
                json.dump(catalog, out_file, indent=4)
        except Exception as error:
            print(error)

if __name__ == '__main__':
    print("main")

    catalog = Catalog()
    catalog.execute("json_reader.json")

#;;; Local Variables: ***
#;;; mode:python ***
#;;; End: ***
