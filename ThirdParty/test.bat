@echo on

docker exec renderapps python /pipeline/make_state_table_ext_multi_pseudoz.py ^
--projectDirectory /mnt/data/M33 ^
--outputFile /mnt/data/M33/scripts/test2 ^
--oneribbononly True ^
--ribbon 4 ^
--session 1 ^
--section 0

echo "Done with the statetable"

docker exec renderapps python -m renderapps.dataimport.create_fast_stacks ^
--render.host W10DTMJ03EG6Z.corp.alleninstitute.org ^
--render.client_scripts /shared/render/render-ws-java-client/src/main/scripts ^
--render.port 8080  ^
--render.memGB 5G  ^
--log_level INFO  ^
--statetableFile /mnt/data/M33/scripts/test2 ^
--render.project test_project ^
--projectDirectory /mnt/data/M33 ^
--outputStackPrefix ACQ_S01 ^
--render.owner test

echo "dfaf"