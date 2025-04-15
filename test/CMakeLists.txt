list(TRANSFORM DRAWABLE_SRC PREPEND "../")
list(TRANSFORM WX_FRAME_SRC PREPEND "../")

add_executable(NodeTest node_test.cpp)
target_link_libraries(NodeTest DrawableLib ${wxWidgets_LIBRARIES}  ${DXFRW_LIB} ${GTEST_LIB_DIR}/libgtest.a Threads::Threads)


add_executable(AppTest app_test.cpp)
target_link_libraries(AppTest DrawableLib ${wxWidgets_LIBRARIES}  ${DXFRW_LIB} ${GTEST_LIB_DIR}/libgtest.a Threads::Threads)
