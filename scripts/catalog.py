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
            "callsign": "noCallsign",
            "centerFreqHz": 0,
            "collectionScript": "unknown",
            "durationSeconds": 0,
            "host": "unknown",
            "key": str(uuid.uuid4()),
            "name": "noName",
            "note": "noNote",
            "receiver": "unknown",
            "sampleRateHz": 0,
            "schemaVersion": 1,
            "site": "unknown",
            "timeStampEpoch": int(time.time()),
            "timeStampIso8601": datetime.now(timezone.utc).isoformat()
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
