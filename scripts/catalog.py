#
# Title: catalog.py
# Description: 
# 
#
import json
import sys
import time

from datetime import datetime, timezone

class Catalog:

    def __init__(self, args: dict[str, str]):
        self.duration = args["duration"]
        self.frequency = args["frequency"]
        self.host = args["host"]
        self.rate = args["rate"]
        self.script = args["script"]
        self.uuid = args["uuid"]

        if self.script.startswith("./"):
            self.script = self.script[2:]

    def execute(self) -> None:

        catalog = {
            "antenna": "unknown",
            "application": self.script,
            "duration": int(self.duration),
            "epoch_time": int(time.time()),
            "host": self.host,
            "json_version": 1,
            "key": self.uuid,
            "note": "none",
            "receiver": "unknown",
            "sample_frequency": int(self.rate),
            "signal_frequency": int(self.frequency),
            "site": "unknown",
            "time_stamp": datetime.now(timezone.utc).isoformat(),
        }

        file_name = f"{self.uuid}.json"
        print(f"creating {file_name}")

        try:
            with open(file_name, "w") as out_file:
                json.dump(catalog, out_file, indent=4)
        except Exception as error:
            print(error)

if __name__ == '__main__':
    if len(sys.argv) > 1:
        args = {
            "uuid": sys.argv[1],
            "duration": sys.argv[2],
            "frequency": sys.argv[3],
            "rate": sys.argv[4],
            "script": sys.argv[5],
            "host": sys.argv[6]
        }

    else:
        args = {}

    catalog = Catalog(args)
    catalog.execute()

#;;; Local Variables: ***
#;;; mode:python ***
#;;; End: ***
