cd debug/ && make runUtest && cd ..
MC_DETERMINISTIC=T debug/utest/runUtest --gtest_output=xml:report.xml
