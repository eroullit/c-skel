FILE(WRITE paths.sh "#!/bin/sh\nPATH_TO_EXEC=${PATH_TO_EXEC}")
FILE(COPY paths.sh DESTINATION ${CMAKE_CURRENT_BINARY_DIR} 
	FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
	GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

FILE(GLOB sharness sharness.sh test-lib.sh fibo.py)
FILE(GLOB test_scripts RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} t[0-9]*.sh)

FOREACH(sharness_file ${sharness})
	EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy ${sharness_file} ${CMAKE_CURRENT_BINARY_DIR})
ENDFOREACH(sharness_file ${sharness})

FOREACH(test_script ${test_scripts})
	EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${test_script} ${CMAKE_CURRENT_BINARY_DIR})
	ADD_TEST(${test_script} sh ${test_script})
ENDFOREACH(test_script ${test_scripts})

