import docker

try:
    client = docker.from_env()
    command = "python -m renderapps.dataimport.create_fast_stacks testing"
    container = client.containers.run("render-p-apps:latest", command, detach=True)
    print(container.logs())

    print("No exception occured..")
except Exception as e:
    print(e)


