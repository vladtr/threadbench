install(
    TARGETS threading_exe
    RUNTIME COMPONENT threading_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
